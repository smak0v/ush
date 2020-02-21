#include "ush.h"

void increase_shell_lvl(char **env) {
    while (*env) {
        char **tmp = mx_strsplit(*env, '=');

        if (!mx_strcmp(tmp[0], "SHLVL")) {
            int shlvl = mx_atoi(tmp[1]);
            char *str_shlvl = mx_itoa(++shlvl);

            free(*env);
            *env = mx_strjoin("SHLVL=", str_shlvl);
            mx_strdel(&str_shlvl);
        }

        mx_del_strarr(&tmp);
        *env++;
    }
}

t_ush *mx_init_shell() {
    extern char **environ;
    t_ush *ush = mx_memalloc(sizeof(t_ush));

    ush->env = mx_strarr_dup(environ);
    increase_shell_lvl(ush->env);
    return ush;
}

void mx_init_signal() {
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void mx_signal_dfl() {
    signal(SIGINT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
