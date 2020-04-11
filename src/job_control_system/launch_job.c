#include "ush.h"

static int fork_and_launch(t_job *job, t_process *process, t_ush *ush,
                           int *fd) {
    int status = MX_SUCCESS;
    pid_t pid = 0;
    int copy_stdout = dup(STDOUT_FILENO);

    if (!job->processes->next && mx_is_builtin(job->processes->argv[0], ush))
        status = mx_launch_simple_builtin(ush, process->argv, copy_stdout);
    else {
        if ((pid = fork()) == 0)
            status = mx_launch_proccess(job->pgid, process, fd, ush);
        else if (pid < 0 && (status = MX_FAILURE))
            mx_proccess_start_error(process->argv[0]);
        else {
            process->pid = pid;
            if (!job->pgid)
                job->pgid = pid;
            setpgid(pid, job->pgid);
            status = mx_wait_and_check_status(ush, job, status, pid);
        }
    }
    return status;
}

static int prepare(t_job *job, t_process *process, t_ush *ush, int *fd) {
    int status = MX_SUCCESS;
    char **env = ush->env;
    char **tmp_env = mx_create_tmp_env(ush, job, process);

    if (!process->argv)
        return mx_clean_data(tmp_env);
    if (tmp_env && *tmp_env)
        ush->env = tmp_env;
    fork_and_launch(job, process, ush, fd);
    mx_del_strarr(&ush->env);
    ush->env = env;
    return status;
}

static int loop_by_processes(t_job *job, t_ush *ush, char **env) {
    t_process *procces = NULL;
    int status = MX_SUCCESS;
    int fd[2] = {job->stdin, 0};
    int pipes[2];

    env = NULL;
    for (procces = job->processes; procces; procces = procces->next) {
        if (procces->next && !pipe(pipes))
            fd[1] = pipes[1];
        else
            fd[1] = job->stdout;
        status = prepare(job, procces, ush, fd);
        if (fd[0] != job->stdin)
            close(fd[0]);
        if (fd[1] != job->stdout)
            close(fd[1]);
        fd[0] = pipes[0];
    }
    return status;
}

int mx_launch_job(t_job *job, t_ush *ush, char **env) {
    if (!mx_strcmp(job->processes->argv[0], "exit") && job->processes->next)
        return MX_SUCCESS;
    if (!mx_strcmp(job->processes->argv[0], "fg") && job->processes->next)
        return mx_no_job_control_error();
    if (mx_strcmp(job->processes->argv[0], "exit"))
        ush->delete_suspended = false;
    return loop_by_processes(job, ush, env);
}
