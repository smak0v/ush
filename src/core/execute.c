#include "ush.h"

static t_builtins *init_builtins() {
    t_builtins *builtins = malloc(sizeof(t_builtins));

    builtins->mx_ush_cd = &mx_ush_cd;
    builtins->mx_ush_pwd = &mx_ush_pwd;
    builtins->mx_ush_env = &mx_ush_env;
    builtins->mx_ush_echo = &mx_ush_echo;
    builtins->mx_ush_exit = &mx_ush_exit;
    builtins->mx_ush_bye = &mx_ush_exit;
    builtins->mx_ush_export = &mx_ush_export;
    builtins->mx_ush_unset = &mx_ush_unset;
    builtins->mx_ush_local = &mx_ush_local;

    return builtins;
}

static int clean_data(char **args, char **tmp_env, char **tmp,
                      int (**builtin_func)(char **, t_ush *)) {
    mx_del_strarr(&args);
    mx_del_strarr(&tmp_env);
    mx_del_strarr(&tmp);
    free(builtin_func);
    builtin_func = NULL;

    return MX_SUCCESS;
}

static void reset_env_and_clean_data(t_ush *ush, char **args, char **tmp,
                                     int (**builtin_func)(char **, t_ush *)) {
    // mx_del_strarr(&args);
    ush->env = tmp;
    free(builtin_func);
    builtin_func = NULL;
}

int mx_execute(char *cmd, t_ush *ush, char **env) {
    int status = MX_SUCCESS;
    char **args = mx_split_cmd(cmd);
    char **tmp_env = mx_create_tmp_env(ush, &args);
    char **tmp = mx_strarr_dup(ush->env);
    int (**builtin_func)(char **, t_ush *) = (
        int (**)(char **, t_ush *))init_builtins();

    if (!args)
        return clean_data(args, tmp_env, tmp, builtin_func);
    if (tmp_env && *tmp_env) {
        mx_del_strarr(&ush->env);
        ush->env = tmp_env;
    }
    mx_setup_underscore_env_var(ush, args[0]);
    for (int i = 0; i < MX_BUILTINS_COUNT; ++i)
        if (!mx_strcmp(args[0], (ush->builtins)[i])) {
            status = builtin_func[i](args, ush);
            reset_env_and_clean_data(ush, args, tmp, builtin_func);
            return status;
        }
    cmd = mx_strarr_to_str(args, " ");
    status = mx_launch(cmd, env);
    reset_env_and_clean_data(ush, args, tmp, builtin_func);
    return status;
}
