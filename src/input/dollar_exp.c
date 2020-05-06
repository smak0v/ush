#include "ush.h"

static char *get_key(char *str) {
    char *key = NULL;

    if (str[0] == '{')
        for (size_t i = 1; i < strlen(str); i++) {
            if (str[i] == '}') {
                key = strndup(str + 1, i - 1);
                break;
            }
            else if (!isalpha(str[i]) && !isnumber(str[i]))
                break;
        }
    else
        for (size_t i = 0; i < strlen(str); i++)
            if (!isalpha(str[i]) && !isnumber(str[i])) {
                key = strndup(str, i == 0? 1 : i);
                break;
            }
    if (!key)
        key = strdup(str);
    return key;
}

void mx_expand_dollar(t_ush *ush, char **line, size_t index) {
    char *key = NULL;
    char *value = NULL;
    char *before = NULL;
    char *dollar_expression = NULL;

    before = strdup(*line);
    key = get_key(before + index + 1);
    value = strcmp(key, "?") == 0 ? mx_getenv(ush->hidden, key)
        : mx_getenv(ush->local_variables, key);
    dollar_expression = strndup(
        before + index, strlen(key) + 1 + (before[index + 1] == '{' ? 2 : 0));
    mx_strdel(line);
    *line = value
        ? mx_replace_substr(before, dollar_expression, value)
        : mx_replace_substr(before, dollar_expression, " ");
    mx_strdel(&dollar_expression);
    mx_strdel(&value);
    mx_strdel(&key);
    mx_strdel(&before);
}
