#include "libmx.h"

char *mx_strarr_to_str(char **strarr, char *separator) {
    char *str = NULL;
    char *tmp = NULL;

    for (int i = 0; strarr && strarr[i]; i++) {
        tmp = mx_strjoin(str, strarr[i]);
        free(str);
        if (strarr[i + 1]) {
            str = mx_strjoin(tmp, separator);
            free(tmp);
        }
        else
            str = tmp;
    }

    return str;
}
