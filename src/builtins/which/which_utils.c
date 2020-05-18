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

static int check_not_found(char *needle, char **haystack) {
    char *substr = NULL;
    int index = -1;

    for (int i = 0; haystack && haystack[i]; i++) {
        substr = mx_strstr(haystack[i], needle);

        if (substr)
            index = i;
    }
    return index;
}

void mx_print_which(char **args, char **output) {
    int j = 0;
    int last_index = -1;

    for (int i = 0; args[i]; i++) {
        if ((last_index = check_not_found(args[i], output)) == -1)
            printf("%s not found\n", args[i]);
        else {
            while (j <= last_index)
                mx_printstr_endl(output[j++]);
        }
    }
}

void mx_which_usage_error(int *status) {
    mx_print_error_endl("usage: which [-as] program ...");
    *status = 1;
}

char **mx_join_strarr_and_memclean(char ***strarr, char ***add) {
    char ***tmp = strarr;
    char **res = mx_strarr_join(*strarr, *add);

    mx_del_strarr(tmp);
    mx_del_strarr(add);

    return res;
}
