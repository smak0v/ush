#include "ush.h"

// static char *get_key(char *str) {
//     char *variable = NULL;

//     if (strlen(str) > 1 && str[1] == '{') {
//         for (int i = 2; i < strlen(str); i++) {
//             if (str[i] == '}') {
//                 variable = strndup(str + 2, i);
//             }
//             else if (!isalpha(str[i]) && !isnumber(str[i]))
                
//         }
//     }
//     else {
//         for (int i = 0; i < strlen(str); i++) {
//             if (!isalpha(str[i]) && !isnumber(str[i])) {
//                 variable = strndup(str, i);
//                 break;
//             }
//         }
//     }
//     return variable;
// }

// static void clear_undefined_variable(t_ush *ush, size_t index) {

// }

// void mx_expand_dollar(t_ush *ush, size_t index) {
//     char *key = NULL;
//     char *value = NULL;
//     char *line = ush->in->line;

//     if (index != 0 && !isspace(line[index - 1]))
//         return;
//     key = get_key(line + index);
//     if (key) {
//         value = strcmp(key, "?") == 0 ? mx_getenv(ush->hidden, key)
//             : mx_getenv(ush->local_variables, key);
//     }
//     else {
//         clear_undefined_variable(ush, index);
//     }
// }


void mx_expand_dollar(t_ush *ush, size_t index, char *postfix) {
    char *key = NULL;
    char *value = NULL;
    char *line = ush->in->line;
    char *tmp = mx_strdup(line + index + 1);

    for (size_t i = 0; i < strlen(postfix); i++)
        if (isspace(postfix[i]) || postfix[i] == ')' || postfix[i] == '\\'
            || postfix[i] == '`') {
            key = strndup(postfix, i);
            break;
        }
    key = key ? key : strndup(postfix, strlen(postfix));
    value = strcmp(key, "?") == 0 ? mx_getenv(ush->hidden, key)
        : mx_getenv(ush->local_variables, key);
    if (value) {
        if (strlen(value) + strlen(line) >= malloc_size(line))
            ush->in->line = realloc(line, malloc_size(line) + strlen(value));
        memset(line + index, 0, strlen(line + index));
        memmove(line + index, value, strlen(value));
        memmove(line + index + strlen(value),
                tmp + strlen(key), strlen(tmp) - strlen(key));
        mx_strdel(&value);
    }
    mx_strdel(&key);
    mx_strdel(&tmp);
}
