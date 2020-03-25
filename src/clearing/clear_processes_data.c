#include "ush.h"

int mx_clean_data(char **tmp_env) {
    mx_del_strarr(&tmp_env);

    return MX_SUCCESS;
}

void mx_reset_env_and_clean_data(int (**builtin_func)(char **, t_ush *)) {
    free(builtin_func);
    builtin_func = NULL;
}
