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
                key = strndup(str, i);
                break;
            }
    if (!key)
        key = strdup(str);
    return key;
}

void mx_expand_dollar(t_ush *ush, size_t index) {
    char *key = NULL;
    char *value = NULL;
    char *line = ush->in->line;
    char *dollar_expression = NULL;

    if (index != 0 && !isspace(line[index - 1]))
        return;
    key = get_key(line + index + 1);
    value = strcmp(key, "?") == 0 ? mx_getenv(ush->hidden, key)
        : mx_getenv(ush->local_variables, key);
    dollar_expression = strndup(line + index, strlen(key) + 1
        + (line[index + 1] == '{' ? 2 : 0));
    mx_strdel(&ush->in->line);
    ush->in->line = value
        ? mx_replace_substr(line, dollar_expression, value)
        : mx_replace_substr(line, dollar_expression, " ");
    mx_strdel(&dollar_expression);
    mx_strdel(&value);
    mx_strdel(&key);
}
