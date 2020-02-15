#include "ush.h"

int mx_execute(char **args, char **envp) {
    if (!args)
        return 1;
    if (!mx_strcmp(args[0], "cd"))
        return mx_ush_cd(args);
    else if (!mx_strcmp(args[0], "pwd"))
        return mx_ush_pwd();
    else if (!mx_strcmp(args[0], "env"))
        return mx_ush_env(envp);
    else if (!mx_strcmp(args[0], "echo"))
        return mx_ush_echo(args);
    else if (!mx_strcmp(args[0], "exit"))
        return mx_ush_exit();
    return mx_launch(args);
}
