#include "ush.h"

static t_builtins *init_builtins() {
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

    return builtins;
}

static int launch_process(t_process *procces, t_ush *ush) {
    int (**builtin_func)(char **, t_ush *) = (
        int (**)(char **, t_ush *))init_builtins();
    char **tmp = mx_strarr_dup(ush->env);
    int status = MX_SUCCESS;

    for (int i = 0; i < MX_BUILTINS_COUNT; ++i)
        if (!mx_strcmp(procces->argv[0], (ush->builtins)[i])) {
            status = builtin_func[i](procces->argv, ush);
            mx_reset_env_and_clean_data(ush, tmp, builtin_func);
            exit(status);
        }
    if (status = execvp(procces->argv[0], procces->argv) < 0) {
        mx_command_not_found_error(procces->argv[0]);
        exit(status);
    }
    mx_reset_env_and_clean_data(ush, tmp, builtin_func);
    return status;
}

int mx_launch_proccess(t_job *job, t_process *procces, int *fd, t_ush *ush) {
    char **tmp_env = mx_create_tmp_env(ush, &procces->argv);

    if (!procces->argv)
        return mx_clean_data(tmp_env);
    if (tmp_env && *tmp_env) {
        mx_del_strarr(&ush->env);
        ush->env = tmp_env;
    }
    if (procces->next) {
        if (fd[0] != STDIN_FILENO && dup2(fd[0], STDIN_FILENO))
            close(fd[0]);
        if (fd[1] != STDOUT_FILENO && dup2(fd[1], STDOUT_FILENO))
            close(fd[1]);
    }
    else if (fd[0] != STDIN_FILENO)
        dup2(fd[0], STDIN_FILENO);
    return launch_process(procces, ush);
}
