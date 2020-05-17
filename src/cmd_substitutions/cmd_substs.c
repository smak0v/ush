#include "ush.h"

static char *process_output_data(t_ush *ush) {
    char *cmd_subst = mx_file_to_str(ush->cmd_substs_file);
    char *new_cmd_subst = NULL;

    if (ush->cmd_subst_replace_spaces) {
        new_cmd_subst = mx_strndup(cmd_subst, mx_strlen(cmd_subst) - 1);
        mx_strdel(&cmd_subst);
        remove(ush->cmd_substs_file);
        return new_cmd_subst;
    }
    else
        return mx_del_extra_cmd_subst_spaces(ush, cmd_subst);
}

static int get_end_index(char *line, char *open_combination, int j) {
    if (!mx_strcmp(open_combination, "$(")) {
        for (int i = mx_strlen(line); i > j; --i)
            if (line[i] == ')' && line[i - 1] != '\\')
                return i;
    }
    else if (!mx_strcmp(open_combination, "`")) {
        for (int i = mx_strlen(line); i > j ; --i)
            if (line[i] == '`')
                return i;
    }
    return -1;
}

static void process_substitution(t_ush *ush, char **line, int i, int end) {
    char *new_line = NULL;
    char *new_cmd_subst = NULL;

    if (mx_check_double_quote(i, *line))
        ush->cmd_subst_replace_spaces = true;
    new_line = mx_strndup(*line + i + ush->open_comb_len,
                          end - i - ush->open_comb_len);
    mx_command_substitutions(ush, &new_line);
    ush->cmd_subst = true;
    mx_remove_back_slashes(&new_line);
    mx_create_trees(ush, &ush->cmd_subst_trees, new_line);
    mx_strdel(&new_line);
    mx_process_commands_list(ush, &ush->cmd_subst_trees);
    new_cmd_subst = process_output_data(ush);
    mx_change_line(line, &new_cmd_subst, i, end);
    ush->cmd_subst_replace_spaces = false;
}

int mx_command_substitutions(t_ush *ush, char **line) {
    int end = -1;

    for (int i = 0; i < mx_strlen(*line); ++i) {
        ush->open_comb_len = 0;
        if ((*line)[i] == '$' && (i + 1 < mx_strlen(*line))
            && (*line)[i + 1] == '(')
            ush->open_comb_len = 2;
        else if ((*line)[i] == '`')
            ush->open_comb_len = 1;
        if (ush->open_comb_len > 0) {
            if (mx_check_single_quote(i, *line))
                break;
            if ((end = get_end_index(*line, ush->open_comb_len == 1
                ? "`" : "$(", i)) && end < 0)
                return mx_multiline_input_error(ush);
            process_substitution(ush, line, i, end);
        }
    }
    return MX_SUCCESS;
}
