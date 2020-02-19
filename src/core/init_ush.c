#include "ush.h"

t_list *mx_create_env_list(char **environ) {
    t_list *env_list = NULL;
    t_env *env = NULL;
    char **tmp = NULL;

    while (*environ) {
        tmp = mx_strsplit(*environ, '=');
        env = mx_memalloc(sizeof(t_env));
        env->key = mx_strdup(tmp[0]);
        if (!mx_strcmp(env->key, "SHLVL")) {
            env->value = mx_itoa(mx_atoi(tmp[1]) + 1);
            setenv(env->key, env->value, 1);
        }
        else
            env->value = mx_strdup(tmp[1]);
        mx_del_strarr(&tmp);
        mx_push_back(&env_list, env);
        environ++;
    }
    return env_list;
}

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
