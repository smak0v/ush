#include "ush.h"

char **mx_safe_split(char *arg) {
    char **split = NULL;

    if (mx_get_char_index(arg, '=') != -1)
        split = mx_split_key_value(arg);
    else
        split = mx_strsplit(arg, '=');

    return split;
}

char **mx_split_key_value(char *str) {
    char **result = malloc(sizeof(char *) * 3);
    char *key = NULL;
    char *value = mx_strdup((char *)mx_memchr(str, '=', mx_strlen(str)) + 1);
    int value_len = mx_strlen(value);
    int strlen = mx_strlen(str);

    key = malloc(sizeof(char) * (strlen - value_len));
    mx_strncpy(key, str, strlen - value_len - 1);
    key[strlen - value_len - 1] = '\0';
    result[0] = key;
    result[1] = value;
    result[2] = NULL;

    return result;
}
