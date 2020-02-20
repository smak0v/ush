#include "ush.h"

t_ush *mx_init_shell() {
    extern char **environ;
    t_ush *ush = mx_memalloc(sizeof(t_ush));
    ush->env = mx_create_env_list(environ);
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
