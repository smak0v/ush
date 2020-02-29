#include "ush.h"

static void process_u(char **env, char *u) {
    while (env && *env) {
        char **tmp = mx_split_key_value(*env);

        if (!mx_strcmp(tmp[0], u)) {
            free(*env);
            for (int i = 0; env[i]; i++)
                env[i] = env[i + 1];

            mx_del_strarr(&tmp);
            break;
        }

        mx_del_strarr(&tmp);
        env++;
    }
}

static void process_P(t_env *env) {
    char *full_path = NULL;
    char *tmp = NULL;

    if (env->P[mx_strlen(env->P) - 1] == '/')
        full_path = mx_strjoin(env->P, *(env->util));
    else {
        tmp = mx_strjoin(env->P, "/");
        full_path = mx_strjoin(tmp, *(env->util));
        free(tmp);
    }

    free(env->util[0]);
    env->util[0] = full_path;
}

static char **set_environment(t_env *env, t_ush *ush) {
    char **environment = NULL;

    if (env->i)
        environment = mx_strarr_dup(env->name_val);
    else
        environment = mx_strarr_join(ush->env, env->name_val);

    return environment;
}

static void execute(t_ush *ush, t_env *env, char **environment) {
    char *cmd = mx_strarr_to_str(env->util, " ");

    mx_execute(cmd, ush, environment);
    mx_strdel(&cmd);
}

int mx_env(t_env *env, t_ush *ush) {
    char **environment = NULL;
    char **tmp_env = mx_strarr_dup(ush->env);

    environment = set_environment(env, ush);
    ush->env = environment;
    if (env->u && !env->i)
        process_u(environment, env->u);
    if (env->P && env->util)
        process_P(env);
    if (!env->util)
        env->util = mx_strsplit("env", ' ');
    if (!mx_strcmp("env", env->util[0]) && !env->util[1])
        mx_print_strarr(environment, "\n");
    else
        execute(ush, env, environment);

    ush->env = tmp_env;
    mx_del_strarr(&environment);
    return 0;
}
