#include "ush.h"

void mx_change_line(t_ush *ush, char **new_cmd_subst, int start, int end) {
    char *new_line = mx_strndup(ush->in->line, start);
    char *tmp = mx_strjoin(new_line, *new_cmd_subst);

    mx_strdel(&new_line);
    new_line = tmp;
    tmp = mx_strjoin(new_line, ush->in->line + start + end + 1);
    mx_strdel(&new_line);
    new_line = tmp;
    mx_strdel(&ush->in->line);
    ush->in->line = new_line;
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

bool mx_check_quote(int index, char *line) {
    for (int i = index; i > 0; --i) {
        while (mx_isspace(line[i]))
            --i;
        if (line[i] == '"' || line[i] == '\'')
            return true;
        else
            return false;
    }
    return false;
}
