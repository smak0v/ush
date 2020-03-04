#include "ush.h"

char *mx_build_key_value_str(char *key, char *value) {
    char *tmp = mx_strjoin(key, "=");
    char *res = mx_strjoin(tmp, value);

    mx_strdel(&tmp);
    return res;
}

void mx_overwrite_strarr_value(char ***array, char *key, char *value) {
    char **arr = *array;
    char **tmp_arr = NULL;
    char *key_value = mx_build_key_value_str(key, value);
    char *tmp = NULL;

    for (int i = 0; arr[i]; i++) {
        if (mx_get_char_index(arr[i], '=') != -1)
            tmp_arr = mx_split_key_value(arr[i]);
        else
            tmp_arr = mx_strsplit(arr[i], '=');
        if (!mx_strcmp(tmp_arr[0], key)) {
            tmp = arr[i];
            arr[i] = mx_strdup(key_value);
            mx_strdel(&tmp);
            mx_del_strarr(&tmp_arr);
            break;
        }
        mx_del_strarr(&tmp_arr);
    }
    mx_strdel(&key_value);
}
