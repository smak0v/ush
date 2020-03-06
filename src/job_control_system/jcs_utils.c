#include "ush.h"

void mx_kill_suspended_jobs(t_job *jobs) {
    t_job *tmp = jobs;

    while (tmp) {
        kill(tmp->pgid, SIGKILL);
        tmp = tmp->next;
    }
}
