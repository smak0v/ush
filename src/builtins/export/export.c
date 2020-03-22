#include "ush.h"

static char *check_for_local_value(char **local, char *key) {
    for (int i = 0; local[i]; i++) {
        if (!mx_strncmp(local[i], key, mx_strlen(key))) {
            return mx_strdup(local[i]);
        }
    }

    return NULL;
}

static char *process_only_key(t_ush *ush, char *arg, char **split) {
    char *tmp = check_for_local_value(ush->local_variables, arg);

    if (!tmp) {
        for (int i = 0; ush->export[i]; i++)
            if (!mx_strcmp(ush->export[i], split[0]))
                return NULL;
        ush->export = mx_add_var(ush->export, split[0]);
        mx_bubble_sort(ush->export, mx_strarr_len(ush->export));
    }
    return tmp;
}

void export_to_export(t_ush *ush, char **split, char *tmp) {
    if (mx_check_duplicate(&ush->export, split[0]))
        mx_overwrite_strarr_value(&ush->export, split[0], split[1]);
    else {
        ush->export = mx_add_var(ush->export, tmp);
        mx_bubble_sort(ush->export, mx_strarr_len(ush->export));
    }
}

void process_export(t_ush *ush, char ***strarr, char **str) {
    char **split = *strarr;
    char *tmp = *str;

    mx_del_strarr(&split);
    split = mx_split_key_value(tmp);
    setenv(split[0], split[1], 1);
    if (mx_check_duplicate(&ush->env, split[0]))
        mx_overwrite_strarr_value(&ush->env, split[0], split[1]);
    else
        ush->env = mx_add_var(ush->env, tmp);

    export_to_export(ush, split, tmp);

    if (mx_check_duplicate(&ush->local_variables, split[0]))
        mx_overwrite_strarr_value(&ush->local_variables, split[0], split[1]);
    else
        ush->local_variables = mx_add_var(ush->local_variables, tmp);

    mx_strdel(str);
    mx_del_strarr(&split);
}

void mx_export(char **arguments, t_ush *ush, int *status) {
    char **split = NULL;
    char *tmp = NULL;

    for (int i = 0; arguments[i]; ++i) {
        split = mx_safe_split(arguments[i]);
        if (mx_check_identifier_validity(split, 0)) {
            mx_invalid_identifier("export", arguments[i]);
            *status = 1;
            continue;
        }
        if (mx_strarr_len(split) < 2) {
            tmp = process_only_key(ush, arguments[i], split);
            if (!tmp) {
                mx_del_strarr(&split);
                continue;
            }
        }
        tmp = tmp != NULL ? tmp : mx_strdup(arguments[i]);
        process_export(ush, &split, &tmp);
    }
}
