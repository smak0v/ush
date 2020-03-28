#include "ush.h"

static char *process_output_data(t_ush *ush) {
    char *cmd_subst = mx_file_to_str(ush->cmd_substs_file);
    char *new_cmd_subst = NULL;
    int j = 0;

    for (int i = 0; i < mx_strlen(cmd_subst) - 1; ++i) {
        new_cmd_subst = realloc(new_cmd_subst, mx_strlen(new_cmd_subst) + 2);
        if (mx_isspace(cmd_subst[i])) {
            new_cmd_subst[j] = ' ';
            while (mx_isspace(cmd_subst[i]))
                ++i;
            --i;
        }
        else
            new_cmd_subst[j] = cmd_subst[i];
        new_cmd_subst[++j] = '\0';
    }
    remove(ush->cmd_substs_file);
    mx_strdel(&cmd_subst);
    return new_cmd_subst;
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
                                         int start) {
    int end_index = get_end_index(ush->in->line + start, open_combination);
    char *new_cmd_subst = NULL;
    char *str = NULL;

    if (end_index < 0) {
        mx_print_error("ush: multiline input not supported\n");
        mx_strdel(&ush->in->line);
        return;
    }
    if (!mx_strcmp(open_combination, "$("))
        str = mx_strndup(ush->in->line + start + 2, end_index - 2);
    else if (!mx_strcmp(open_combination, "`"))
        str = mx_strndup(ush->in->line + start + 1, end_index - 1);
    ush->cmd_subst = true;
    mx_create_trees(ush, str);
    mx_strdel(&str);
    mx_process_commands_list(ush);
    mx_clear_trees(ush);
    new_cmd_subst = process_output_data(ush);
    mx_change_line(ush, &new_cmd_subst, start, end_index);
}

void mx_command_substitutions(t_ush *ush) {
    for (int i = 0; i < mx_strlen(ush->in->line); ++i) {
        if (ush->in->line[i] == '$' && (i + 1 < mx_strlen(ush->in->line))
            && ush->in->line[i + 1] == '(') {
                if ((i - 1 >= 0) && ush->in->line[i - 1] == '\\')
                    continue;
                process_command_substitution(ush, "$(", i);
                i = 0;
            }
        else if (ush->in->line[i] == '`') {
            if ((i - 1 >= 0) && ush->in->line[i - 1] == '\\')
                continue;
            process_command_substitution(ush, "`", i);
            i = 0;
        }
    }
}
