#include "ush.h"

static int found_key_in_strarr(char **strarr, char *str) {
    for (int i = 0; strarr[i]; i++) {
        char **tmp = mx_strsplit(strarr[i], '=');

        if (!mx_strcmp(tmp[0], str)) {
                mx_del_strarr(&tmp);
                return 1;
        }

        mx_del_strarr(&tmp);
    }
    return 0;
}

void mx_unset(t_ush *ush, char **arg, int *status) {
    for (int i = 0; i < mx_strarr_len(arg); i++) {
        int len = mx_strlen(arg[i]);

        if (mx_check_identifier_validity(arg[i], 0)) {
            mx_invalid_identifier("unset", arg[i]);
            *status = 1;
            continue;
        }
        if (found_key_in_strarr(ush->env, arg[i])) {
            ush->env = mx_popn_string_array(ush->env, arg[i], len);
            unsetenv(arg[i]);
        }
        if (found_key_in_strarr(ush->export, arg[i]))
            ush->export = mx_popn_string_array(ush->export, arg[i], len);
        if (found_key_in_strarr(ush->local_variables, arg[i])) {
            ush->local_variables = mx_popn_string_array(ush->local_variables,
                                                        arg[i], len);
        }
    }
    mx_del_strarr(&arg);
}
