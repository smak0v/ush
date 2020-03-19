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

int get_jobs_max_index(t_job *jobs) {
    t_job *tmp = jobs;
    int index = 0;

    while (tmp) {
        if (tmp->index > index)
            index = tmp->index;
        tmp = tmp->next;
    }
    return index;
}

int mx_get_job_index(t_job *jobs, t_job *job) {
    t_job *tmp = jobs;
    int index = 0;

    if (!tmp)
        return 0;
    while (tmp->next)
        tmp = tmp->next;
    while (tmp) {
        if (tmp->pgid == job->pgid)
            return index + 1;
        ++index;
        tmp = tmp->prev;
    }
    return -1;
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
    int index = -1;

    waitpid(pid, &status, WUNTRACED|WCONTINUED);
    while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status))
        waitpid(pid, &status, WUNTRACED|WCONTINUED);
    if (WIFSTOPPED(status)) {
        index = mx_get_job_index(ush->suspended, job);
        if ((index == 0 && !ush->suspended) || (index < 0))
            mx_push_front_job(&ush->suspended, mx_copy_job(job));
        mx_printstr("\n[");
        mx_printint(ush->suspended->index);
        mx_printstr("]+  Stopped                 ");
        mx_printstr_endl(job->cmd);
    }
    else if (WIFSIGNALED(status) && mx_printnbr('\n'))
        mx_delete_suspended_job(&ush->suspended, job->pgid);
    else if (WIFEXITED(status))
        mx_delete_suspended_job(&ush->suspended, job->pgid);
    return status;
}
