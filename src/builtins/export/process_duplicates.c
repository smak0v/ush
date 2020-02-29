#include "ush.h"

static void overwrite_local(t_ush *ush, char *arg, char *key) {
    char *tmp = NULL;
    char **tmp_arr = NULL;

    for (int i = 0; ush->local_variables[i]; i++) {
        if (mx_get_char_index(ush->local_variables[i], '=') != -1)
            tmp_arr = mx_split_key_value(ush->local_variables[i]);
        else
            tmp_arr = mx_strsplit(ush->local_variables[i], '=');
        if (!mx_strcmp(tmp_arr[0], key)) {
                tmp = ush->local_variables[i];
                ush->local_variables[i] = mx_strdup(arg);
                mx_strdel(&tmp);
                mx_del_strarr(&tmp_arr);
                break;
        }
        mx_del_strarr(&tmp_arr);
    }
}

static void overwrite_export_and_local(t_ush *ush, char *arg, char *key) {
    char *tmp = NULL;
    char **tmp_arr = NULL;

    for (int i = 0; ush->export[i]; i++) {
        if (mx_get_char_index(ush->local_variables[i], '=') != -1)
            tmp_arr = mx_split_key_value(ush->local_variables[i]);
        else
            tmp_arr = mx_strsplit(ush->local_variables[i], '=');
        if (!mx_strcmp(tmp_arr[0], key)) {
            tmp = ush->export[i];
            ush->export[i] = mx_strdup(arg);
            mx_strdel(&tmp);
            mx_del_strarr(&tmp_arr);
            break;
        }
        mx_del_strarr(&tmp_arr);
    }
    overwrite_local(ush, arg, key);
}

int mx_process_duplicate(t_ush *ush, char *arg, char *key) {
    char *tmp = NULL;

    for (int i = 0; ush->env[i]; i++) {
        char **tmp_arr = mx_split_key_value(ush->env[i]);
        if (!mx_strcmp(tmp_arr[0], key)) {
            tmp = ush->env[i];
            ush->env[i] = mx_strdup(arg);
            mx_strdel(&tmp);
            setenv(key, (char *)memchr(arg, '=', strlen(arg)) + 1, 1);
            overwrite_export_and_local(ush, arg, key);
            mx_del_strarr(&tmp_arr);
            return 1;
        }
        mx_del_strarr(&tmp_arr);
    }

    return 0;
}
