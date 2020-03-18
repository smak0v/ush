#include "ush.h"

static char *clear_fg_arg(char *job_arg) {
    bool flag = false;
    char *tmp = NULL;
    int len = mx_strlen(job_arg);

    for (int i = 0; i < len; ++i) {
        if (job_arg[i] == '%' && !flag)
            continue;
        if (job_arg[i] == '%' && flag)
            return -1;
        flag = true;
        tmp = mx_strndup(&(job_arg[i]), len - i);
        break;
    }
    return tmp;
}

bool mx_job_is_number(char *job_arg) {
    bool flag = false;
    int len = mx_strlen(job_arg);

    for (int i = 0; i < len; ++i) {
        if (job_arg[i] == '%' && !flag)
            continue;
        if (job_arg[i] == '%' && flag)
            return false;
        flag = true;
        if (!mx_isdigit(job_arg[i]))
            return false;
    }
    return true;
}

int mx_get_job_index_by_number(char *job_arg, t_job *jobs) {
    t_job *tmp_job = jobs;
    char *tmp = clear_fg_arg(job_arg);
    int number = tmp ? mx_atoi(tmp) : 1;
    int job_index = -1;
    int i = 0;

    while (tmp_job->next)
        tmp_job = tmp_job->next;
    while (tmp_job) {
        if (tmp_job->index == number) {
            job_index = i;
            break;
        }
        ++i;
        tmp_job = tmp_job->prev;
    }
    mx_strdel(&tmp);
    return job_index;
}


int mx_get_job_index_by_name(char *job_arg, t_job *jobs) {
    t_job *tmp_job = jobs;
    char *tmp = clear_fg_arg(job_arg);
    int job_index = -1;
    int counter = 0;
    int i = 0;

    while (tmp_job->next)
        tmp_job = tmp_job->next;
    while (tmp_job) {
        if (!mx_strncmp(tmp_job->cmd, tmp, mx_strlen(tmp)) && (++i)) {
            if (job_index < 0)
                job_index = counter;
        }
        ++counter;
        tmp_job = tmp_job->prev;
    }
    if (i > 1 && (job_index = -2))
        mx_ambiguous_job_spec_error(job_arg);
    mx_strdel(&tmp);
    return job_index;
}
