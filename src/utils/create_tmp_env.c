#include "ush.h"

static int process_duplicates(char **env, char *arg, char *key) {
    char *tmp = NULL;
    char **tmp_arr = NULL;

    if (!env)
        return 0;
    for (int i = 0; env[i]; ++i) {
        if (mx_get_char_index(env[i], '=' != -1))
            tmp_arr = mx_split_key_value(env[i]);
        else
            tmp_arr = mx_strsplit(env[i], '=');
        if (!mx_strcmp(tmp_arr[0], key)) {
            tmp = env[i];
            env[i] = mx_strdup(arg);
            mx_strdel(&tmp);
            mx_del_strarr(&tmp_arr);
            return 1;
        }
        mx_del_strarr(&tmp_arr);
    }
    return 0;
}

static char **delete_duplicates_except_last(char **env) {
    int len = mx_get_arr_length(env);
    char **tmp_1 = NULL;
    char **tmp_2 = NULL;

    for (int i = len - 1; i >= 0; --i) {
        tmp_1 = mx_strsplit(env[i], '=');
        for (int j = i - 1; j >= 0; --j) {
            tmp_2 = mx_strsplit(env[j], '=');
            if (!mx_strcmp(tmp_1[0], tmp_2[0])) {
                env = mx_pop_string_array(env, env[i]);
                --len;
                i = len - 1;
                mx_del_strarr(&tmp_2);
                break;
            }
            mx_del_strarr(&tmp_2);
        }
        mx_del_strarr(&tmp_1);
    }
    return env;
}

static char **create_tmp_env(char ***args, bool *command_found) {
    int len = mx_get_arr_length(*args);
    char **tmp_env = NULL;
    char **pair = NULL;

    for (int i = 0; i < len; ++i) {
        if (mx_get_char_index(*args[i], '=') >= 0) {
            pair = mx_strsplit(*args[i], '=');
            if (!process_duplicates(tmp_env, *args[i], pair[0]))
                tmp_env = mx_add_var(tmp_env, *args[i]);
            mx_del_strarr(&pair);
            *args = mx_pop_string_array(*args, *args[i]);
            --i;
            --len;
        }
        else {
            *command_found = true;
            break;
        }
    }
    return tmp_env;
}

char **mx_create_tmp_env(t_ush *ush, t_job *job, t_process *process) {
    bool command_found = false;
    char **tmp_env = create_tmp_env(&process->argv, &command_found);
    char **tmp = NULL;

    if (!command_found && tmp_env && *tmp_env && !job->processes->next) {
        tmp = mx_strarr_join(tmp_env, ush->local_variables);
        mx_del_strarr(&ush->local_variables);
        ush->local_variables = tmp;
        ush->local_variables =
            delete_duplicates_except_last(ush->local_variables);
        return NULL;
    }
    tmp = mx_strarr_join(tmp_env, ush->env);
    mx_del_strarr(&tmp_env);
    tmp_env = tmp;
    tmp_env = delete_duplicates_except_last(tmp_env);
    return tmp_env;
}
