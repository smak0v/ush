#include "ush.h"

void mx_unset(t_ush *ush, char **arg) {
    for (int i = 0; i < mx_strarr_len(arg); i++) {
        if (mx_check_identifier_validity(arg[i], 0)) {
            mx_invalid_identifier("unset", arg[i]);
            continue;
        }
        unsetenv(arg[i]);

        ush->env = mx_popn_string_array(ush->env, arg[i], mx_strlen(arg[i]));
        ush->export = mx_popn_string_array(ush->export, arg[i], 
                                           mx_strlen(arg[i]));
        ush->local_variables = mx_popn_string_array(ush->local_variables,
                                                    arg[i], mx_strlen(arg[i]));
    }
    mx_del_strarr(&arg);
}
