#include "ush.h"

static char *check_for_local_value(char **local, char *key) {
    for (int i = 0; local[i]; i++)
        if (!mx_strncmp(local[i], key, mx_strlen(key)))
            return mx_strdup(local[i]);

    return NULL;
}

static void save_to_export(t_ush *ush, char *key) {
    char *new_var[] = {key, NULL};
    char **tmp = ush->export;

    ush->export = mx_strarr_join(ush->export, new_var);
    mx_bubble_sort(ush->export, mx_strarr_len(ush->export));
    mx_del_strarr(&tmp);
}

static void save_everywhere(t_ush *ush, char *key_value, char **split) {
    char **for_setenv = mx_split_key_value(key_value);
    char *for_arrays[] = {key_value, NULL};
    char **tmp = NULL;

    setenv(for_setenv[0], for_setenv[1], 1);

    tmp = ush->env;
    ush->env = mx_strarr_join(ush->env, for_arrays);
    mx_del_strarr(&tmp);

    tmp = ush->export;
    ush->export = mx_strarr_join(ush->export, for_arrays);
    mx_bubble_sort(ush->export, mx_strarr_len(ush->export));
    mx_del_strarr(&tmp);

    tmp = ush->local_variables;
    ush->local_variables = mx_strarr_join(ush->local_variables, for_arrays);
    mx_del_strarr(&tmp);
    mx_del_strarr(&split);
}

static char *process_only_key(t_ush *ush, char *arg, char **split) {
    char *tmp = check_for_local_value(ush->local_variables, arg);
    if (!tmp) {
        save_to_export(ush, split[0]);
        mx_del_strarr(&split);
    }
    return tmp;
}

void mx_export(char **arguments, t_ush *ush) {
    char **split = NULL;
    char *tmp = NULL;

    for (int i = 0; arguments[i]; i++) {
        split = mx_strsplit(arguments[i], '=');
        if (mx_check_identifier_validity(split[0], 0)) {
            mx_invalid_identifier("export", arguments[i]);
            mx_del_strarr(&split);
            continue;
        }
        //mx_process_duplicates(ush, arguments[i], split[0]);
        if (mx_strarr_len(split) < 2) {
            tmp = process_only_key(ush, arguments[i], split);
            if (!tmp)
                continue;
        }
        tmp = tmp ? tmp : mx_strdup(arguments[i]);
        save_everywhere(ush, tmp, split);
        mx_strdel(&tmp);
    }
}
