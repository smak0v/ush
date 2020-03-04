#include "ush.h"

int (*builtin_func[]) (char **, t_ush *) = {
    &mx_ush_cd,
    &mx_ush_pwd,
    &mx_ush_env,
    &mx_ush_echo,
    &mx_ush_exit,
    &mx_ush_exit,
    &mx_ush_export,
    &mx_ush_unset,
    &mx_ush_local,
    &mx_ush_which
};

int mx_execute(char *cmd, t_ush *ush, char **env) {
    char **args = NULL;
    char *tmp = cmd;

    if (!cmd)
        return 1;
    args = mx_split_cmd(cmd);
    for (int i = 0; i < MX_BUILTINS_COUNT; ++i)
        if (!mx_strcmp(args[0], (ush->builtins)[i]))
            return (*builtin_func[i])(args, ush);
    mx_del_strarr(&args);
    return mx_launch(cmd, env);
}
