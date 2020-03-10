#include "ush.h"

t_job *mx_create_job(char *cmd) {
    t_job *job = calloc(1, sizeof(t_job));

    job->cmd = mx_strdup(cmd);
    job->processes = mx_create_processes(job->cmd);
    return job;
}

t_job *mx_copy_job(t_job *job) {
    t_job *new_job = calloc(1, sizeof(t_job));

    new_job->cmd = mx_strdup(job->cmd);
    new_job->pgid = job->pgid;
    new_job->processes = mx_copy_processes(job->processes);
    return new_job;
}

void mx_delete_job(t_job **job) {
    mx_strdel(&(*job)->cmd);
    mx_delete_processes(&(*job)->processes);
    free(*job);
    *job = NULL;
}

void mx_push_front_job(t_job **jobs, t_job *job) {
    job->next = *jobs;
    if (*jobs)
        (*jobs)->prev = job;
    *jobs = job;
}

int mx_suspended_jobs_list_size(t_job *suspended_jobs) {
    t_job *job = suspended_jobs;
    int size = 0;

    while (job) {
        ++size;
        job = job->next;
    }
    return size;
}
