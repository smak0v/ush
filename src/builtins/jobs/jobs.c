#include "ush.h"

int mx_ush_jobs(char **args, t_ush *ush) {
    t_job *tmp = ush->suspended;
    int size = mx_suspended_jobs_list_size(ush->suspended);
    int count = 0;

    mx_printstr_endl("JOBS");
    if (!size)
        return MX_SUCCESS;
    while (tmp) {
        mx_printchar('[');
        mx_printint(++count);
        mx_printchar(']');
        if (count == size)
            mx_printstr("+  ");
        else if (count == size - 1)
            mx_printstr("-  ");
        else
            mx_printchar_ntimes(' ', 3);
        mx_printstr("Stopped");
        mx_printchar_ntimes(' ', 17);
        mx_printstr_endl(tmp->cmd);
        tmp = tmp->next;
    }
    return MX_SUCCESS;
}
