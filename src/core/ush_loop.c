#include "ush.h"

int mx_ush_loop(t_ush *ush) {
    int status = 0;

    while (!ush->exit) {
        mx_printstr("u$h> ");
        ush->in->line = mx_get_line(ush);
        mx_expansions(ush);
        mx_create_trees(ush, ush->in->line);
        // ush->in->line = mx_proccess_escapings(line)
        status = mx_proccess_commands_list(ush);
        mx_clear_trees(ush);
        mx_strdel(&ush->in->line);
    }
    return status;
}
