#include "ush.h"

void mx_change_line(char **line, char **new_cmd_subst, int start, int end) {
    char *new_line = mx_strndup((*line), start);
    char *tmp = mx_strjoin(new_line, *new_cmd_subst);

    mx_strdel(&new_line);
    new_line = tmp;
    tmp = mx_strjoin(new_line, (*line) + start + end + 1);
    mx_strdel(&new_line);
    new_line = tmp;
    mx_strdel(line);
    *line = new_line;
    mx_strdel(new_cmd_subst);
}

char *mx_del_extra_cmd_subst_spaces(t_ush *ush, char *cmd_subst) {
    char *new_cmd_subst = mx_strnew(0);
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

bool mx_check_double_quote(int index, char *line) {
    --index;

    while (mx_isspace(line[index]) && (index >= 0))
        --index;

    return (line[index] == '"') ? true : false;
}

bool mx_check_singly_quote(int index, char *line) {
    --index;

    while (mx_isspace(line[index]) && (index >= 0))
        --index;

    return (line[index] == '\'') ? true : false;
}
