#include "ush.h"

static void increase_shell_lvl(char **env) {
    int found = 0;

    while (env && *env) {
        char **tmp = mx_split_key_value(*env);

        if (!mx_strcmp(tmp[0], "SHLVL")) {
            int shlvl = mx_atoi(tmp[1]);
            char *str_shlvl = mx_itoa(++shlvl);

            free(*env);
            *env = mx_strjoin("SHLVL=", str_shlvl);
            mx_strdel(&str_shlvl);
            found = 1;
        }

        mx_del_strarr(&tmp);
        env++;
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
        char **tmp = mx_split_key_value(*env);

        process_unfound(not_found, tmp[0]);
        setenv(tmp[0], tmp[1], 1);
        mx_del_strarr(&tmp);
        env++;
    }

    return not_found;
}

static void init_shell_for_jobs_and_cmd_substs(t_ush *ush) {
    struct termios tty;

    while (tcgetpgrp(STDIN_FILENO) != (ush->pgid = getpgrp()))
        kill(-ush->pgid, SIGTTIN);
    mx_ignore_signals();
    ush->pgid = getpid();
    setpgid(ush->pgid, ush->pgid);
    tcsetpgrp(STDIN_FILENO, ush->pgid);
    tcgetattr(STDIN_FILENO, &tty);
    ush->cmd_substs_file = mx_get_cmd_substs_filename();
    remove(ush->cmd_substs_file);
}

t_ush *mx_init_shell(void) {
    extern char **environ;
    t_ush *ush = mx_memalloc(sizeof(t_ush));
    char *builtins[] = {"cd", "pwd", "echo", "which", "exit", "bye", "env",
                        "export", "unset", "local", "jobs", "fg", "history",
                        "return", NULL};
    int *not_found = NULL;

    init_shell_for_jobs_and_cmd_substs(ush);
    mx_init_terminal_data();
    ush->in = mx_memalloc(sizeof(t_input));
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
