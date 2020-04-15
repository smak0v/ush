#include "ush.h"

t_builtins *mx_init_builtins(void) {
    t_builtins *builtins = malloc(sizeof(t_builtins));

    builtins->mx_ush_cd = &mx_ush_cd;
    builtins->mx_ush_pwd = &mx_ush_pwd;
    builtins->mx_ush_echo = &mx_ush_echo;
    builtins->mx_ush_which = &mx_ush_which;
    builtins->mx_ush_exit = &mx_ush_exit;
    builtins->mx_ush_bye = &mx_ush_exit;
    builtins->mx_ush_env = &mx_ush_env;
    builtins->mx_ush_export = &mx_ush_export;
    builtins->mx_ush_unset = &mx_ush_unset;
    builtins->mx_ush_local = &mx_ush_local;
    builtins->mx_ush_jobs = &mx_ush_jobs;
    builtins->mx_ush_fg = &mx_ush_fg;
    builtins->mx_ush_history = &mx_ush_history;
    builtins->mx_ush_return = &mx_ush_return;
    builtins->mx_ush_true = &mx_ush_true;
    builtins->mx_ush_false = &mx_ush_false;

    return builtins;
}
