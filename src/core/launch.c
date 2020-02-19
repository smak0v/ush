#include "ush.h"

int mx_launch(char **args, t_ush *ush) {
    pid_t pid = 0;
    int status = 0;

    ush++; // Remove
    pid = fork();
    if (!pid) {
        status = execvp(args[0], args);
        if (status < 0)
            mx_print_error("ush: command not found: ");
            mx_print_error_endl(args[0]);
        exit(status);
    }
    else {
        waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status))
            waitpid(pid, &status, WUNTRACED);
    }
    return 1;
}
