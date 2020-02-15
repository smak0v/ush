#include "ush.h"

int mx_launch(char **args) {
    pid_t pid = 0;
    int status = 0;

    pid = fork();
    if (!pid)
        execvp(args[0], args);
    else {
        waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status))
            waitpid(pid, &status, WUNTRACED);
    }
    return 1;
}
