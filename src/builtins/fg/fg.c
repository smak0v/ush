#include "ush.h"

static int fg(t_ush *ush, t_job *job) {
    int status = MX_SUCCESS;

    tcsetpgrp(STDIN_FILENO, job->pgid);
    tcsetattr(ush->pgid, TCSADRAIN, &job->tmodes);
    kill(-job->pgid, SIGCONT);
    status = mx_wait_and_check_status(ush, job, status, job->pgid);
    tcsetpgrp(STDIN_FILENO, ush->pgid);
    tcgetattr(STDIN_FILENO, &job->tmodes);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &ush->savetty);
    return status;
}

static bool is_job_number(char *job_arg) {
    bool flag = false;

    for (int i = 0; i < mx_strlen(job_arg); ++i) {
        if (job_arg[i] == '%' && !flag)
            continue;
        flag = true;
        if (!mx_isdigit(job_arg[i]))
            return false;
    }
    return true;
}

static t_job *find_job_by_number(char *job_arg, t_job *jobs) {
    bool flag = false;
    t_job *job = NULL;
    t_job *tmp_job = jobs;
    char *tmp = NULL;
    int number = 0;
    int counter = 1;

    for (int i = 0; i < mx_strlen(job_arg); ++i) {
        if (job_arg[i] == '%' && !flag)
            continue;
        if (job_arg[i] == '%' && flag)
            break;
        flag = true;
        tmp = mx_strndup(&(job_arg[i]), mx_strlen(job_arg) - i);
        number = mx_atoi(tmp);
        mx_strdel(&tmp);
    }
    while (tmp_job)
        tmp_job = tmp_job->next;
    while (tmp_job->prev) {
        if (counter == number)
            job = tmp_job;
        ++counter;
        tmp_job = tmp_job->prev;
    }
    return job;
}

int mx_ush_fg(char **args, t_ush *ush) {
    int status = MX_SUCCESS;
    char *job_arg = NULL;
    t_job *job = NULL;

    if (ush->suspended) {
        if (mx_get_arr_length(args) > 1)
            job_arg = args[1];
        if (job_arg) {
            if (is_job_number(job_arg))
                job = find_job_by_number(job_arg, ush->suspended);
            else
                job = NULL;
            if (!job)
                mx_no_such_job_error(job_arg);
            else {
                mx_printstr_endl(job->cmd);
                status = fg(ush, job);
            }
        }
        else {
            job = ush->suspended;
            mx_printstr_endl(job->cmd);
            status = fg(ush, job);
        }
    }
    else {
        mx_printstr("ush: fg: current: no such job\n");
        status = MX_FAILURE;
    }
    return status;
}
