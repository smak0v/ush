#include "ush.h"

static bool check_path(char *postfix) {
    char *user_path = NULL;
    char *path = NULL;
    struct stat pstat;
    bool result;

    for (size_t i = 0; i < strlen(postfix); i++)
        if (isspace(postfix[i]) || postfix[i] == ')' || postfix[i] == '`') {
            if (i - 1 > 0 && postfix[i - 1] == '\\')
                continue;
            user_path = strndup(postfix, i);
            break;
        }
    user_path = user_path ? user_path : strndup(postfix, strlen(postfix));
    path = mx_strjoin("/Users/", user_path);
    mx_strdel(&user_path);
    result = stat(path, &pstat) < 0 ? false : true;
    mx_strdel(&path);
    return result;
}

static char *replace_tilde(t_ush *ush, char *postfix) {
    char *tilde = NULL;

    if (postfix[0] == '+' || postfix[0] == '-') {
        if (strlen(postfix) > 1 && !isspace(postfix[1]))
            if (!(postfix[1] == '`' || postfix[1] == ')'))
                return NULL;
        tilde = postfix[0] == '+' ? mx_getenv(ush->hidden, "PWD")
            : mx_getenv(ush->hidden, "OLDPWD");
    }
    else if (!postfix[0] || isspace(postfix[0]) || postfix[0] == '/'
        || postfix[0] == '`' || postfix[0] == ')') {
            tilde = mx_getenv(ush->hidden, "HOME");
        }
    else
        tilde = check_path(postfix) ? strdup("/Users/") : NULL;
    return tilde;
}

void mx_expand_tilde(t_ush *ush, size_t index, char *postfix) {
    char *tilde = NULL;
    char *line = ush->in->line;
    char *tmp = mx_strdup(line + index + 1);

    if (index != 0 && !isspace(line[index - 1])) {
        mx_strdel(&tmp);
        return;
    }
    tilde = replace_tilde(ush, postfix);
    if (tilde) {
        if (strlen(tilde) + strlen(line) >= malloc_size(line))
            ush->in->line = realloc(line, malloc_size(line) + strlen(tilde));
        memmove(line + index, tilde, strlen(tilde));
        memmove(line + index + strlen(tilde),
                tmp + (tmp[0] == '+' || tmp[0] == '-'), strlen(tmp));
        mx_strdel(&tilde);
    }
    mx_strdel(&tmp);
}
