#include "ush.h"

static void print_suspended_job(t_list *job, t_job *jobs) {
    mx_printchar('[');
    mx_printint(((t_builtin_job *)job->data)->index);
    mx_printchar(']');
    if (((t_builtin_job *)job->data)->pgid == jobs->pgid)
        mx_printstr("+  ");
    else if (jobs->next
             && (((t_builtin_job *)job->data)->pgid == jobs->next->pgid)) {
        mx_printstr("-  ");
    }
    else
        mx_printchar_ntimes(' ', 3);
    mx_printstr("Stopped");
    mx_printchar_ntimes(' ', 17);
    mx_printstr_endl(((t_builtin_job *)job->data)->cmd);
}

static bool job_builtin_comparator(void *data_1, void *data_2) {
    t_builtin_job *d_1 = (t_builtin_job *)data_1;
    t_builtin_job *d_2 = (t_builtin_job *)data_2;

    if (d_1->index > d_2->index)
        return true;
    return false;
}

static t_list *create_jobs_list(t_job *jobs) {
    t_job *tmp = jobs;
    t_list *list = NULL;
    t_builtin_job *job = NULL;

    while (tmp) {
        job = malloc(sizeof(t_builtin_job));
        job->index = tmp->index;
        job->pgid = tmp->pgid;
        job->cmd = mx_strdup(tmp->cmd);
        mx_push_front(&list, job);
        tmp = tmp->next;
    }
    list = mx_sort_list(list, job_builtin_comparator);
    return list;
}

static void delete_jobs_list(t_list **list) {
    t_builtin_job *job = NULL;
    t_list *tmp = NULL;

    while (*list) {
        tmp = *list;
        job = (t_builtin_job *)tmp->data;
        mx_strdel(&job->cmd);
        free(job);
        job = NULL;
        mx_pop_front(list);
    }
}

int mx_ush_jobs(char **args, t_ush *ush) {
    t_job *tmp = ush->suspended;
    t_list *jobs = NULL;
    t_list *temp = NULL;

    ush->delete_suspended = true;
    if (!mx_suspended_jobs_list_size(ush->suspended))
        return MX_SUCCESS;
    jobs = create_jobs_list(tmp);
    temp = jobs;
    while (temp) {
        print_suspended_job(temp, tmp);
        temp = temp->next;
    }
    delete_jobs_list(&jobs);
    return MX_SUCCESS;
}
