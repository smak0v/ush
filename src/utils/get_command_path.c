#include "ush.h"

void mx_get_command_path(t_ush *ush, t_process *process) {
    int which_status = MX_SUCCESS;
    char **args = malloc(sizeof(char *) * 2);
    char **command = NULL;

    args[0] = mx_strdup(process->argv[0]);
    args[1] = NULL;
    command = mx_which(ush, NULL, args, &which_status);
    if (which_status == MX_SUCCESS && command && *command)
        process->argv[0] = command[0];
    mx_del_strarr(&args);
}
