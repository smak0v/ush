#include "ush.h"

// TODO (now testing version)
void mx_execute_piped(char **args, char **piped_args) {
    int pipe_fd[2];
    pid_t pipe_1;
    pid_t pipe_2;
    int status = 0;

    pipe_1 = fork();
    if (pipe_1 < 0) {
        mx_print_error("ush: error starting a new proccess: ");
        mx_print_error_endl(args[0]);
        return;
    }
    if (pipe_1 == 0) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        if ((status = execvp(pipe_fd[0], args)) < 0) {
            mx_print_error("ush: command not found: ");
            mx_print_error_endl(args[0]);
            exit(status);
        }
    }
    else {
        pipe_2 = fork();
        if (pipe_2 < 0) {
            mx_print_error("ush: error starting a new proccess: ");
            mx_print_error_endl(piped_args[0]);
            return;
        }
        if (pipe_2 == 0) {
            close(pipe_fd[1]);
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);
            if ((status = execvp(piped_args[0], piped_args)) < 0) {
                mx_print_error("ush: command not found: ");
                mx_print_error_endl(args[0]);
                exit(status);
            }
        }
        else {
            wait(NULL);
            wait(NULL);
        }
    }
}
