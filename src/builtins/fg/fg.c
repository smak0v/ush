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

static int fg(char **args, t_ush *ush) {
     t_job *job = ush->suspended;

    // tcsetpgrp(STDIN_FILENO, job->pgid);
    mx_default_signals();
    if ((kill(-job->pgid, SIGCONT)) < 0) {
        printf("ush: fg %d: job not found\n", job->pgid);
        return MX_FAILURE;
    }
    return MX_SUCCESS;
}

int mx_ush_fg(char **args, t_ush *ush) {
    t_job *next = NULL;
    t_job *job = NULL;
    pid_t pid = 0;
    int status = MX_SUCCESS;

    if (ush->suspended) {
        job = ush->suspended;
        next = job->next;
        mx_printstr_endl(job->cmd);
        if ((pid = fork()) == 0)
            status = fg(args, ush);
        else if (pid < 0) {
            status = MX_FAILURE;
            mx_proccess_start_error(args[0]);
        }
        else {
            setpgid(pid, job->pgid);
            waitpid(pid, &status, WUNTRACED|WCONTINUED);
            while (!WIFEXITED(status)
                   && !WIFSIGNALED(status)
                   && !WIFSTOPPED(status))
                waitpid(pid, &status, WUNTRACED|WCONTINUED);
            check_status(ush, job, status);
        }
        mx_delete_job(&job);
        ush->suspended = next;
        if (ush->suspended)
            ush->suspended->prev = NULL;
    }
    else
        mx_printstr("ush: fg: current: no such job\n");
    return MX_SUCCESS;
}
