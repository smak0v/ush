#include "ush.h"

static int exec_proc(int in, int out, t_cmd *cmd, bool last) {
    int status = SUCCESS;

    if (!last) {
        if (in != STDIN_FILENO) {
            dup2(in, STDIN_FILENO);
            close(in);
        }
        if (out != STDOUT_FILENO) {
            dup2(out, STDOUT_FILENO);
            close(out);
        }
    }
    else if (in != STDIN_FILENO)
        dup2(in, STDIN_FILENO);
    if ((status = execvp(cmd->args[0], (char **)cmd->args)) < 0) {
        mx_command_not_found_error(cmd->args[0]);
        exit(status);
    }
    return status;
}

static int spawn_and_exec_proc(int in, int out, t_cmd *cmd, bool last) {
    pid_t pid = 0;
    int status = SUCCESS;

    if ((pid = fork()) == 0)
        exec_proc(in, out, cmd, last);
    else if (pid < 0) {
        status = FAILURE;
        mx_proccess_start_error(cmd->args[0]);
    }
    else {
        waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status))
            waitpid(pid, &status, WUNTRACED);
    }
    return status;
}

static int launch(int n, t_cmd *cmd) {
    pid_t pid = 0;
    int status = SUCCESS;
    int i = 0;
    int in = 0;
    int fd[2];

    for (i = 0; i < n; ++i) {
        pipe(fd);
        if (i < n - 1)
            status = spawn_and_exec_proc(in, fd[1], cmd + i, false);
        else
            status = spawn_and_exec_proc(in, fd[1], cmd + i, true);
        close(fd[1]);
        in = fd[0];
    }
    return status;
}

int mx_launch(char *cmd) {
    char **splited_by_pipes = mx_strsplit(cmd, '|');
    char **tmp = splited_by_pipes;
    char *trimmed = NULL;
    t_cmd *commands = calloc((mx_get_arr_length(tmp) + 1), sizeof(t_cmd *));
    int count = -1;

    while (*tmp) {
        trimmed = mx_strtrim(*tmp);
        commands[++count].args = mx_split_cmd(trimmed);
        mx_strdel(&trimmed);
        ++tmp;
    }
    mx_del_strarr(&splited_by_pipes);
    return launch(mx_get_arr_length(commands), commands);
}
