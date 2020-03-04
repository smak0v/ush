#include "ush.h"

int mx_check_duplicate(char ***array, char *key) {
    char **arr = *array;
    char **tmp_arr = NULL;

    for (int i = 0; arr[i]; ++i) {
        tmp_arr = mx_safe_split(arr[i]);

        if (!mx_strcmp(tmp_arr[0], key)) {
            mx_del_strarr(&tmp_arr);
            return 1;
        }
        mx_del_strarr(&tmp_arr);
    }
    return 0;
}

