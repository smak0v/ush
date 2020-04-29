#include "ush.h"

void mx_ush_core(t_ush *ush) {
    char *str_exit_code = NULL;

    mx_expansions(ush);
    mx_command_substitutions(ush);
    ush->cmd_subst = false;
    if (ush->in->line) {
        ush->cmd_trees = mx_create_trees(ush, ush->in->line);
        ush->exit_code = mx_process_commands_list(ush, ush->cmd_trees);
        ush->exit_code = ush->exit_code > 0 ? 1 : 0;
        str_exit_code = mx_itoa(ush->exit_code);
        mx_overwrite_strarr_value(&ush->hidden, "?", str_exit_code);
        mx_strdel(&str_exit_code);
        mx_clear_trees(ush, ush->cmd_trees);
        mx_strdel(&ush->in->line);
    }
}

int mx_ush_loop(t_ush *ush) {
    while (!ush->exit) {
        tcsetpgrp(STDIN_FILENO, ush->pgid);
        mx_update_prompt(ush);
        mx_print_prompt(ush);
        ush->in->line = mx_get_line(ush);
        mx_ush_core(ush);
    }
    return ush->exit_code;
}
