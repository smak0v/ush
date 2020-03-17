#include "ush.h"

static int fg(t_ush *ush, int job_index) {
    t_job *job = ush->suspended;
    int status = MX_SUCCESS;
    int counter = -1;

    while (job->next)
        job = job->next;
    while (job) {
        if (++counter == job_index)
            break;
        job = job->prev;
    }
    mx_printstr_endl(job->cmd);
    tcsetpgrp(STDIN_FILENO, job->pgid);
    tcsetattr(ush->pgid, TCSADRAIN, &job->tmodes);
    kill(-job->pgid, SIGCONT);
    status = mx_wait_and_check_status(ush, job, status, job->pgid);
    tcsetpgrp(STDIN_FILENO, ush->pgid);
    tcgetattr(STDIN_FILENO, &job->tmodes);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &ush->savetty);
    return status;
}

static int fg_with_arguments(t_ush *ush, char *arg) {
    int status = MX_SUCCESS;
    int job_index = -1;

    if (mx_job_is_number(arg))
        job_index = mx_get_job_index_by_number(arg, ush->suspended);
    else
        job_index = mx_get_job_index_by_name(arg, ush->suspended);
    if (job_index == -1) {
        mx_no_such_job_error(arg);
        status = MX_FAILURE;
    }
    else if (job_index == -2)
        status = MX_FAILURE;
    else
        status = fg(ush, job_index);
    return status;
}

int mx_ush_fg(char **args, t_ush *ush) {
    int status = MX_SUCCESS;

    if (ush->suspended) {
        if (mx_get_arr_length(args) > 1 && args[1])
            status = fg_with_arguments(ush, args[1]);
        else
            status = fg(ush, 0);
    }
    else {
        mx_no_such_job_error("current");
        status = MX_FAILURE;
    }
    return status;
}
