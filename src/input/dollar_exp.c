#include "ush.h"

void mx_expand_dollar(t_ush *ush, size_t index, char *postfix) {
    char *key = NULL;
    char *value = NULL;
    char *line = ush->in->line;
    char *tmp = mx_strdup(line + index + 1);

    for (size_t i = index; i < strlen(postfix); i++)
        if (isspace(postfix[i]))
            key = strndup(postfix, i);
    key = key ? key : strndup(postfix, strlen(line));
    value = mx_getenv(ush->hidden, key);
    if (value) {
        if (strlen(value) + strlen(line) >= malloc_size(line))
            ush->in->line = realloc(line, malloc_size(line) + strlen(value));
        memmove(line + index, value, strlen(value));
        memmove(line + index + strlen(value),
                tmp + strlen(key), strlen(tmp) - strlen(key));
        mx_strdel(&value);
    }
    mx_strdel(&key);
    mx_strdel(&tmp);
}
