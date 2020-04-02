#include "ush.h"

int mx_ush_loop(t_ush *ush) {
    char *str_exit_code = NULL;

    while (!ush->exit) {
        tcsetpgrp(STDIN_FILENO, ush->pgid);
        mx_printstr("u$h> ");
        ush->in->line = mx_get_line(ush);
        mx_expansions(ush);
        mx_create_trees(ush, ush->in->line);
        ush->exit_code = mx_proccess_commands_list(ush);
        str_exit_code = mx_itoa(ush->exit_code);
        mx_overwrite_strarr_value(&ush->hidden, "?", str_exit_code);
        mx_strdel(&str_exit_code);
        mx_clear_trees(ush);
        mx_strdel(&ush->in->line);
    }
    return ush->exit_code;
}
