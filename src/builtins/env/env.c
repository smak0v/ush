#include "ush.h"

static void process_u(char **env, char *u) {
    while (env && *env) {
        char **tmp = mx_strsplit(*env, '=');

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

int mx_env(t_env *env, t_ush *ush) {
    char **environment = NULL;
    char **tmp_env = mx_strarr_dup(ush->env);

    if (env->i)
        environment = mx_strarr_dup(env->name_val);
    else
        environment = mx_strarr_dup(ush->env);
    
    ush->env = environment;

    if (env->u) {
        process_u(environment, env->u);
    }

    if (!env->util|| (!mx_strcmp("env", env->util[0]) && !env->util[1]))
        mx_print_strarr(environment, "\n");
    else {
        char *cmd = mx_strarr_to_str(env->util, " ");
        mx_execute(cmd, ush, environment);
    }

    if (tmp_env)
        ush->env = tmp_env;
    mx_del_strarr(&environment);
    return 0;
}
