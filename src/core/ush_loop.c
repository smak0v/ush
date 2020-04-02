#include "ush.h"

int mx_ush_loop(t_ush *ush) {
    while (!ush->exit) {
        tcsetpgrp(STDIN_FILENO, ush->pgid);
        mx_printstr("u$h> ");
        ush->in->line = mx_get_line(ush);
        mx_expansions(ush);
        mx_command_substitutions(ush);
        ush->cmd_subst = false;
        if (ush->in->line) {
            mx_create_trees(ush, ush->in->line);
            ush->exit_code = mx_process_commands_list(ush);
            mx_clear_trees(ush);
            mx_strdel(&ush->in->line);
        }
    }
    return ush->exit_code;
}
