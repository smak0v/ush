#include "ush.h"

int spawn_proc(int in, int out, t_cmd *cmd) {
    pid_t pid = 0;
    int status = 0;

    if ((pid = fork()) == 0) {
        if (in != STDOUT_FILENO) {
            dup2(in, STDOUT_FILENO);
            close(in);
        }
        if (out != STDOUT_FILENO) {
            dup2(out, STDOUT_FILENO);
            close(out);
        }
        if ((status = execvp(cmd->argv[0], (char **)cmd->argv)) < 0) {
            mx_print_error("ush: command not found: ");
            mx_print_error_endl(cmd->argv[0]);
        }
        return status;
    }
    return 0;
}

int fork_pipes(int n, t_cmd *cmd) {
    pid_t pid = 0;
    int status = 0;
    int i = 0;
    int in = 0;
    int fd[2];

    for (i = 0; i < n - 1; ++i) {
        pipe(fd);
        status = spawn_proc(in, fd[1], cmd + i);
        close(fd[1]);
        in = fd[0];
    }
    if (in != STDIN_FILENO)
        dup2(in, STDIN_FILENO);
    if ((pid = fork()) == 0) {
        if ((status = execvp(cmd[i].argv[0], (char **) cmd[i].argv)) < 0) {
            mx_print_error("ush: command not found: ");
            mx_print_error_endl(cmd->argv[0]);
        }
        return status;
    }
    return status;
}

int mx_execute_piped(char *cmd) {
    char **splited_by_pipes = mx_strsplit(cmd, '|');
    char **tmp = splited_by_pipes;
    char *trimmed = NULL;
    t_cmd *commands = calloc((mx_get_arr_length(tmp) + 1), sizeof(t_cmd *));
    int count = -1;

    while (*tmp) {
        trimmed = mx_strtrim(*tmp);
        commands[++count].argv = mx_split_cmd(trimmed);
        mx_strdel(&trimmed);
        ++tmp;
    }
    mx_del_strarr(&splited_by_pipes);
    return fork_pipes(mx_get_arr_length(commands), commands);
}
