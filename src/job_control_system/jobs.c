#include "ush.h"

t_job *mx_create_job(char *cmd) {
    t_job *job = calloc(1, sizeof(t_job));

    job->cmd = mx_strdup(cmd);
    job->processes = mx_create_processes(job->cmd);
    return job;
}

void mx_delete_job(t_job **job) {
    mx_strdel(&(*job)->cmd);
    mx_delete_processes(&(*job)->processes);
    free(*job);
    *job = NULL;
}
