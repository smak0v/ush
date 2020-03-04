#include "ush.h"

char *select_flags(t_blt builtin) {
    if (builtin == env)
        return mx_strdup(MX_ENV_FLAGS);
    else if (builtin == cd)
        return mx_strdup(MX_CD_FLAGS);
    else if (builtin == pwd)
        return mx_strdup(MX_PWD_FLAGS);
    else if (builtin == which)
        return mx_strdup(MX_WHICH_FLAGS);
    else if (builtin == echo)
        return mx_strdup(MX_ECHO_FLAGS);
    return NULL;
}

char *mx_flags_validation(char **flags, t_blt builtin) {
    char *allowed_flags = select_flags(builtin);
    char *error = NULL;
    int status = -1;

    while (*flags) {
        status = -1;
        for (int i = 0; allowed_flags[i]; i++) {
            if (*flags[0] == allowed_flags[i])
                status = 0;
        }
        if (status == -1) {
            error = *flags;
            break;
        }
        flags++;
    }

    mx_strdel(&allowed_flags);
    return error;
}
