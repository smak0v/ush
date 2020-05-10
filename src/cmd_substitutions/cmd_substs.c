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

static int get_end_index(char *line, char *open_combination) {
    if (!mx_strcmp(open_combination, "$(")) {
        for (int i = 2; i < mx_strlen(line); ++i)
            if (line[i] == ')' && line[i - 1] != '\\')
                return i;
    }
    else if (!mx_strcmp(open_combination, "`")) {
        for (int i = 1; i < mx_strlen(line); ++i)
            if (line[i] == '`' && line[i - 1] != '\\')
                return i;
    }
    return -1;
}

static void process_command_substitution(t_ush *ush, char *open_combination,
                                         int start, char **line) {
    int end_index = get_end_index((*line) + start, open_combination);
    char *new_cmd_subst = NULL;
    char *str = NULL;

    if (end_index < 0) {
        mx_print_error("ush: multiline input not supported\n");
        mx_strdel(&ush->in->line);
        return;
    }
    if (!mx_strcmp(open_combination, "$("))
        str = mx_strndup((*line) + start + 2, end_index - 2);
    else if (!mx_strcmp(open_combination, "`"))
        str = mx_strndup((*line) + start + 1, end_index - 1);
    ush->cmd_subst = true;
    mx_create_trees(ush, &ush->cmd_subst_trees, str);
    mx_strdel(&str);
    mx_process_commands_list(ush, &ush->cmd_subst_trees);
    new_cmd_subst = process_output_data(ush);
    mx_change_line(line, &new_cmd_subst, start, end_index);
}

static void command_substitutions(t_ush *ush, int i, char *open_combination,
                                  char **line) {
    if (mx_check_double_quote(i, *line))
        ush->cmd_subst_replace_spaces = true;
    process_command_substitution(ush, open_combination, i, line);
    ush->cmd_subst_replace_spaces = false;
}

void mx_command_substitutions(t_ush *ush, char **line, int start) {
    for (int i = start; i < mx_strlen(*line); ++i) {
        if ((*line)[i] == '$' && (i + 1 < mx_strlen(*line))
            && (*line)[i + 1] == '(') {
            if (mx_check_single_quote(i, *line))
                break;
            if ((i - 1 >= 0) && (*line)[i - 1] == '\\')
                continue;
            mx_command_substitutions(ush, line, i + 2);
            command_substitutions(ush, i, "$(", line);
        }
        else if ((*line)[i] == '`') {
            if (ush->cmd_subst_level == 0 && mx_check_single_quote(i, *line))
                break;
            if (ush->cmd_subst_level == 0 && (i - 1 >= 0)
                && (*line)[i - 1] == '\\')
                continue;
            mx_command_substitutions(ush, line, i + 1);
            command_substitutions(ush, i, "`", line);
        }
    }
}
