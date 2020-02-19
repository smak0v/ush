#include "ush.h"

int mx_ush_loop(t_ush *ush) {
    char *line = NULL;
    int status = 0;

    while (1) {
        mx_printstr("u$h> ");
        line = mx_get_line(ush);
        mx_create_trees(ush, line);
        status = mx_proccess_commands_list(ush);
        mx_clear_trees(ush);
        mx_strdel(&line);
    }
    return status;
}
