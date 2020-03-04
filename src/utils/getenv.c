#include "ush.h"

char *mx_getenv(char **env, char *key) {
    char **tmp_arr = NULL;
    char *res;

    if (!env)
        return NULL;
    for (int i = 0; env[i]; ++i) {
        if (mx_get_char_index(env[i], '=') != -1) {
            tmp_arr = mx_split_key_value(env[i]);

            if (!mx_strcmp(tmp_arr[0], key) && tmp_arr[1]) {
                res = mx_strdup(tmp_arr[1]);
                mx_del_strarr(&tmp_arr);
                return res;
            }

            mx_del_strarr(&tmp_arr);
        }
    }

    return NULL;
}
