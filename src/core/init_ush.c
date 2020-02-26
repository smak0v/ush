#include "ush.h"

static void increase_shell_lvl(char **env) {
    int found = 0;

    while (env && *env) {
        char **tmp = mx_strsplit(*env, '=');

        if (!mx_strcmp(tmp[0], "SHLVL")) {
            int shlvl = mx_atoi(tmp[1]);
            char *str_shlvl = mx_itoa(++shlvl);

            free(*env);
            *env = mx_strjoin("SHLVL=", str_shlvl);
            mx_strdel(&str_shlvl);
            found = 1;
        }

        mx_del_strarr(&tmp);
        *env++;
    }
}

static void process_unfound(int *not_found, char *key) {
        if (!mx_strcmp("OLDPWD", key))
            not_found[OLDPWD] = 1;
        else if (!mx_strcmp("PWD", key))
            not_found[PWD] = 1;
        else if (!mx_strcmp("SHLVL", key))
            not_found[SHLVL] = 1;
        else if (!mx_strcmp("PATH", key))
            not_found[PATH] = 1;
        else if (!mx_strcmp("TERM", key))
            not_found[TERM] = 1;
        else if (!mx_strcmp("HOME", key))
            not_found[HOME] = 1;
}

static int *set_env(char **env) {
    int *not_found = calloc(6, sizeof(int));

    while (env && *env) {
        char **tmp = mx_strsplit(*env, '=');

        process_unfound(not_found, tmp[0]);
        setenv(tmp[0], tmp[1], 1);
        mx_del_strarr(&tmp);
        env++;
    }

    return not_found;
}

t_ush *mx_init_shell(void) {
    extern char **environ;
    t_ush *ush = mx_memalloc(sizeof(t_ush));
    char *builtins[] = {"cd", "pwd", "env", "echo", "exit", "bye",
                           "export", "unset", "local", NULL};
    int *not_found = NULL;

    ush->env = mx_strarr_dup(environ);
    increase_shell_lvl(ush->env);
    not_found = set_env(ush->env);

    ush->export = mx_strarr_dup(ush->env);
    ush->local_variables = mx_strarr_dup(ush->env);
    mx_set_default(ush, not_found);
    mx_bubble_sort(ush->export, mx_strarr_len(ush->export) - 1);
    ush->builtins = mx_strarr_dup(builtins);

    return ush;
}
