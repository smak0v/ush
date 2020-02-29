#include "ush.h"

static int choose_exec(char **args, char **env) {
    // if (!env)
        return execvp(args[0], args);
    // else
    //     return execve(args[0], args, env);
}

static int exec_proc(int *pipe_fd, t_cmd *cmd, bool last, char **env) {
    int status = MX_SUCCESS;

    if (!last) {
        if (pipe_fd[0] != STDIN_FILENO) {
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);
        }
        if (pipe_fd[1] != STDOUT_FILENO) {
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[1]);
        }
    }
    else if (pipe_fd[0] != STDIN_FILENO)
        dup2(pipe_fd[0], STDIN_FILENO);
    if ((status = choose_exec((char **)cmd->args, env)) < 0) {
        mx_command_not_found_error(cmd->args[0]);
        exit(status);
    }
    return status;
}

static int spawn_and_exec_proc(int *pipe_fd, t_cmd *cmd, bool last, char **env) {
    pid_t pid = 0;
    int status = MX_SUCCESS;

    if ((pid = fork()) == 0) {
        exec_proc(pipe_fd, cmd, last, env);
    }
    else if (pid < 0) {
        status = MX_FAILURE;
        mx_proccess_start_error(cmd->args[0]);
    }
    else {
        waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status))
            waitpid(pid, &status, WUNTRACED);
    }
    return status;
}

static int launch(int n, t_cmd *cmd, char **env) {
    pid_t pid = 0;
    int status = MX_SUCCESS;
    int i = 0;
    int pipe_fd[2] = {0, 0};
    int fd[2];

    for (i = 0; i < n; ++i) {
        pipe(fd);
        pipe_fd[1] = fd[1];
        if (i < n - 1)
            status = spawn_and_exec_proc(pipe_fd, cmd + i, false, env);
        else
            status = spawn_and_exec_proc(pipe_fd, cmd + i, true, env);
        close(fd[1]);
        pipe_fd[0] = fd[0];
    }
    return status;
}

int mx_launch(char *cmd, char **env) {
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
    return launch(mx_get_arr_length(commands), commands, env);
}
