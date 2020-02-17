#include "ush.h"

char *builtins[] = {"cd", "pwd", "env", "echo", "exit"};

int (*builtin_func[]) (char **, t_ush *) = {
    &mx_ush_cd,
    &mx_ush_pwd,
    &mx_ush_env,
    &mx_ush_echo,
    &mx_ush_exit
};

static int ush_count_builtins() {
    return sizeof(builtins) / sizeof(char *);
}

int mx_execute(char **args, t_ush *ush) {
    if (!args && !(*args))
        return 1;
    for (int i = 0; i < ush_count_builtins(); ++i)
        if (!mx_strcmp(args[0], builtins[i]))
            return (*builtin_func[i])(args, ush);
    return mx_launch(args, ush);
}
