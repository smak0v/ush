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

static int get_job_index_by_name(t_job *jobs, char *tmp, char *job_arg) {
    t_job *tmp_job = jobs;
    int job_index = -1;
    int counter = 0;
    int i = 0;

    while (tmp_job) {
        if (!mx_strncmp(tmp_job->cmd, tmp, mx_strlen(tmp)) && (++i)) {
            if (job_index < 0)
                job_index = counter;
        }
        ++counter;
        tmp_job = tmp_job->next;
    }
    if (i > 1 && (job_index = -2))
        mx_ambiguous_job_spec_error(job_arg);
    mx_strdel(&tmp);
    return job_index;
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

    while (tmp_job) {
        if (tmp_job->index == number) {
            job_index = i;
            break;
        }
        ++i;
        tmp_job = tmp_job->next;
    }
    mx_strdel(&tmp);
    return job_index;
}

int mx_get_job_index_by_name(char *job_arg, t_job *jobs) {
    char *tmp = clear_fg_arg(job_arg);

    if (tmp && mx_strlen(tmp) > 0 && tmp[0] == '+') {
        mx_strdel(&tmp);
        return 0;
    }
    else if (tmp
             && (mx_strlen(tmp) == 1 && tmp[0] == '-')
             || (mx_strlen(tmp) == 2 && tmp[0] == '-' && tmp[1] == '-')) {
        mx_strdel(&tmp);
        return jobs->next ? 1 : 0;
    }
    else if (tmp && mx_strlen(tmp) > 1 && tmp[0] == '-') {
        mx_invalid_option_error(tmp);
        mx_strdel(&tmp);
        return -2;
    }
    else
        return get_job_index_by_name(jobs, tmp, job_arg);
}
