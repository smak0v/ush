#include "ush.h"

static void delete_suspended_job(t_job **suspended_jobs, t_job *job) {
    if (!(*suspended_jobs) || !job)
        return;
    if (*suspended_jobs == job)
        *suspended_jobs = job->next;
    if (job->next)
        job->next->prev = job->prev;
    if (job->prev)
        job->prev->next = job->next;
    mx_delete_job(&job);
}

void mx_kill_suspended_jobs(t_job *jobs) {
    t_job *tmp = jobs;

    while (tmp) {
        kill(tmp->pgid, SIGKILL);
        tmp = tmp->next;
    }
}

void mx_delete_suspended_job(t_job **suspended_jobs, pid_t pgid) {
    t_job *current = *suspended_jobs;

    if (!(*suspended_jobs) || pgid < 0)
        return;
    while (current) {
        if (current->pgid == pgid)
            break;
        current = current->next;
    }
    if (!current)
        return;
    delete_suspended_job(suspended_jobs, current);
}

int mx_wait_and_check_status(t_ush *ush, t_job *job, int status, pid_t pid) {
    t_job *job_copy = mx_copy_job(job);

    waitpid(pid, &status, WUNTRACED|WCONTINUED);
    while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status))
        waitpid(pid, &status, WUNTRACED|WCONTINUED);
    if (WIFSTOPPED(status)) {
        mx_delete_suspended_job(&ush->suspended, job->pgid);
        mx_printstr("\n[");
        mx_printint(mx_suspended_jobs_list_size(ush->suspended) + 1);
        mx_printstr("]+  Stopped                 ");
        mx_printstr_endl(job_copy->cmd);
        mx_push_front_job(&ush->suspended, mx_copy_job(job_copy));
    }
    else if (WIFSIGNALED(status) && mx_printnbr('\n'))
        mx_delete_suspended_job(&ush->suspended, job->pgid);
    else if (WIFEXITED(status))
        mx_delete_suspended_job(&ush->suspended, job->pgid);
    mx_delete_job(&job_copy);
    return status;
}
