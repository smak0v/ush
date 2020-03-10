#include "ush.h"

static void check_status(t_ush *ush, t_job *job, int status) {
    if (WIFSTOPPED(status)) {
        mx_printstr("\n[");
        mx_printint(mx_suspended_jobs_list_size(ush->suspended) + 1);
        mx_printstr("]+  Stopped                 ");
        mx_printstr_endl(job->cmd);
        mx_push_front_job(&ush->suspended, mx_copy_job(job));
    }
}

static int fork_and_launch(t_job *job, t_process *procces, t_ush *ush,
                           int *fd) {
    int status = MX_SUCCESS;
    pid_t pid = 0;

    if ((!mx_strcmp(procces->argv[0], "exit")
        || (!mx_strcmp(procces->argv[0], "bye")))
        && !procces->next)
        status = mx_ush_exit(procces->argv, ush);
    else {
        if ((pid = fork()) == 0)
            status = mx_launch_proccess(job->pgid, procces, fd, ush);
        else if (pid < 0) {
            status = MX_FAILURE;
            mx_proccess_start_error(procces->argv[0]);
        }
        else {
            procces->pid = pid;
            if (!job->pgid)
                job->pgid = pid;
            setpgid(pid, job->pgid);
            waitpid(pid, &status, WUNTRACED|WCONTINUED);
            while (!WIFEXITED(status)
                   && !WIFSIGNALED(status)
                   && !WIFSTOPPED(status))
                waitpid(pid, &status, WUNTRACED|WCONTINUED);
            check_status(ush, job, status);
        }
    }
    return status;
}

int mx_launch_job(t_job *job, t_ush *ush, char **env) {
    int status = MX_SUCCESS;
    t_process *procces = NULL;
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
