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

char *mx_get_cmd_substs_filename(void) {
    return mx_strjoin(getenv("HOME"), MX_CMD_SUBST_FILE);
}
