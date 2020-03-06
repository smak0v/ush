#include "ush.h"

int mx_ush_fg(char **args, t_ush *ush) {
    pid_t last_job_pid = ush->suspended->pgid;

    mx_printstr_endl("FG");
    kill(last_job_pid, SIGCONT);
    return MX_SUCCESS;
}
