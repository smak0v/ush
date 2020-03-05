#include "ush.h"

static int fork_and_launch(t_job *job, t_process *procces, t_ush *ush,
                           int *fd) {
    int status = MX_SUCCESS;
    pid_t pid = 0;

    if (!mx_strcmp(procces->argv[0], "exit") && !procces->next)
        status = mx_ush_exit(procces->argv, ush);
    else {
        if ((pid = fork()) == 0)
            status = mx_launch_proccess(job, procces, fd, ush);
        else if (pid < 0) {
            status = MX_FAILURE;
            mx_proccess_start_error(procces->argv[0]);
        }
        else {
            procces->pid = pid;
            if (!job->pgid)
                job->pgid = pid;
            waitpid(pid, &status, WUNTRACED);
            while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status))
                waitpid(pid, &status, WUNTRACED);
        }
    }
    return status;
}

int mx_launch_job(t_job *job, t_ush *ush, char **env) {
    int status = MX_SUCCESS;
    t_process *procces = NULL;
    pid_t pid = 0;
    int fd[2] = {job->stdin, 0};
    int pipes[2];

    for (procces = job->processes; procces; procces = procces->next) {
        if (procces->next && !pipe(pipes))
            fd[1] = pipes[1];
        else
            fd[1] = job->stdout;
        status = fork_and_launch(job, procces, ush, fd);
        if (fd[0] != job->stdin)
            close(fd[0]);
        if (fd[1] != job->stdout)
            close(fd[1]);
        fd[0] = pipes[0];
    }
    return status;
}
