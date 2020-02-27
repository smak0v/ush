#include "ush.h"

int mx_launch(char **args) {
    int status = 0;
    pid_t pid = fork();

    if (!pid) {
        if ((status = execvp(args[0], args)) < 0) {
            mx_print_error("ush: command not found: ");
            mx_print_error_endl(args[0]);
        }
        return status;
    }
    else if (pid < 0) {
        mx_print_error("ush: error starting a new proccess: ");
        mx_print_error_endl(args[0]);
    }
    else {
        waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status))
            waitpid(pid, &status, WUNTRACED);
    }
    return status;
}
