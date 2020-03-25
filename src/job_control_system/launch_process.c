#include "ush.h"

static int launch_process(t_process *process, t_ush *ush) {
    int (**builtin_func)(char **, t_ush *) = (
        int (**)(char **, t_ush *))mx_init_builtins();
    int status = MX_SUCCESS;

    for (int i = 0; i < MX_BUILTINS_COUNT; ++i)
        if (!mx_strcmp(process->argv[0], ush->builtins[i])) {
            status = builtin_func[i](process->argv, ush);
            mx_reset_env_and_clean_data(builtin_func);
            _exit(status);
        }
    if ((status = execvp(process->argv[0], process->argv)) < 0) {
        mx_command_not_found_error(process->argv[0]);
        _exit(status);
    }
    mx_reset_env_and_clean_data(builtin_func);
    _exit(status);
}

static void manage_fds(t_process *process, int *fd) {
    if (process->next) {
        if (fd[0] != STDIN_FILENO) {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        }
        if (fd[1] != STDOUT_FILENO) {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
        }
    }
    else if (fd[0] != STDIN_FILENO)
        dup2(fd[0], STDIN_FILENO);
}

int mx_launch_simple_builtin(t_ush *ush, char **argv) {
    char **tmp_env = mx_create_tmp_env(ush, &argv);
    int (**builtin_func)(char **, t_ush *) = (
        int (**)(char **, t_ush *))mx_init_builtins();
    char **tmp = mx_strarr_dup(ush->env);
    int status = MX_SUCCESS;

    if (!argv)
        return mx_clean_data(tmp_env);
    if (tmp_env && *tmp_env) {
        mx_del_strarr(&ush->env);
        ush->env = tmp_env;
    }
    for (int i = 0; i < MX_BUILTINS_COUNT; ++i)
        if (!mx_strcmp(argv[0], ush->builtins[i])) {
            status = builtin_func[i](argv, ush);
            mx_reset_env_and_clean_data(builtin_func);
        }
    mx_del_strarr(&tmp);
    return status;
}

int mx_launch_proccess(pid_t pgid, t_process *process, int *fd, t_ush *ush) {
    char **tmp_env = mx_create_tmp_env(ush, &process->argv);
    pid_t pid = getpid();

    if (!process->argv)
        return mx_clean_data(tmp_env);
    if (tmp_env && *tmp_env) {
        mx_del_strarr(&ush->env);
        ush->env = tmp_env;
    }
    if (!pgid)
        pgid = pid;
    setpgid(pid, pgid);
    tcsetpgrp(STDIN_FILENO, pgid);
    mx_default_signals();
    manage_fds(process, fd);
    return launch_process(process, ush);
}
