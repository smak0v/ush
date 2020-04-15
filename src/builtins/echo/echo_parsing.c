#include "ush.h"

static bool check_flag_validity(char *arg) {
    for (int i = 1; arg[i]; i++) {
        if (mx_get_char_index(MX_ECHO_FLAGS, arg[i]) == -1)
            return false;
    }

    return true;
}

static char **write_flags(char **flags, char *arg) {
    char **res = flags;
    bool is_unique = true;
    int len = 0;

    arg += 1;
    for (; *arg; arg++) {
        for (int j = 0; res && res[j]; j++)
            if (res[j][0] == *arg)
                is_unique = false;

        if (is_unique) {
            len = mx_strarr_len(res) + 2;  // 1 for new flag && 1 for NULL
            res = realloc(res, len * sizeof(char *));
            res[len - 2] = mx_strndup(arg, 1);
            res[len - 1] = NULL;
        }
    }

    return res;
}

char **mx_echo_parse_flags(char **args) {
    char **flags = NULL;

    for (int i = 1; args[i]; i++) {
        if (args[i][0] == '-') {
            if (!check_flag_validity(args[i]))
                return flags;
            else
                flags = write_flags(flags, args[i]);
        }
        else
            break;
    }

    return flags;
}

char **mx_echo_parse_args(char **args) {
    bool flag_stop = false;
    int i = 1;

    for (; args[i]; i++) {
        if (!flag_stop && args[i][0] == '-' && check_flag_validity(args[i]))
            continue;
        else
            break;
    }

    return mx_strarr_dup(&args[i]);
}
