#include "ush.h"

char **mx_get_split_path(t_ush *ush) {
    char *env_path = getenv("PATH");
    char **path = NULL;

    if (!env_path)
        env_path = mx_getenv(ush->local_variables, "PATH");
    else
        env_path = mx_strdup(env_path);

    path = mx_strsplit(env_path, ':');
    mx_strdel(&env_path);

    return path;
}

void mx_which_usage_error(int *status) {
    mx_print_error_endl("usage: which [-as] program ...");
    *status = 1;
}
