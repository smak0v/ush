#include "ush.h"

// TODO when which will be done
static char **proccess_env_list(char **env, char *arg) {
    int len = mx_get_arr_length(env);
    char **tmp = NULL;
    char **new = NULL;
    char *temp = NULL;

    for (int i = len - 1; i >= 0; --i) {
        tmp = mx_strsplit(env[i], '=');
        if (!mx_strcmp(tmp[0], "_")) {
            env = mx_pop_string_array(env, env[i]);
            temp = mx_strjoin("_=", arg);
            tmp = malloc(2 * sizeof(char *));
            tmp[0] = mx_strdup(temp);
            tmp[1] = NULL;
            mx_strdel(&temp);
            new = mx_strarr_join(env, tmp);
            mx_del_strarr(&env);
            mx_del_strarr(&tmp);
            env = new;
            break;
        }
        mx_del_strarr(&tmp);
    }
    return env;
}

void mx_setup_underscore_env_var(t_ush *ush, char *arg) {
    ush->env = proccess_env_list(ush->env, arg);
    ush->local_variables = proccess_env_list(ush->local_variables, arg);
}
