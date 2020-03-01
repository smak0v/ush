#include "ush.h"

char *mx_get_home(t_ush *ush) {
    char *home = NULL;
    char **tmp = NULL;
    int i = -1;

    while (ush->local_variables[++i] && home == NULL) {
        tmp = mx_strsplit(ush->local_variables[i], '=');
        if (strcmp(tmp[0], "HOME") == 0)
            home = mx_strdup(tmp[1]);
        mx_del_strarr(&tmp);
    }
    return home;
}

void mx_expand_tilde(t_ush *ush, size_t index, char *postfix) {
    char *tmp = mx_strdup(ush->in->line + index + 1);
    char *home = NULL;

    if (index != 0 && !isspace(ush->in->line[index - 1]))
        return;
    if (strcmp(postfix, "+") == 0)
        return; // home = $PWD
    else if (strcmp(postfix, "-") == 0)
        return; // home = $OLDPWD
    else if (!postfix[0] || isspace(postfix[0]) || postfix[0] == '/')
        home = mx_get_home(ush);
    else {
        // struct stat stat;
        // char *path = NULL;

        // home = strdup("/Users/");
        // path = mx_strjoin()
        // if (stat(, &path))
    }
    if (strlen(home) + strlen(ush->in->line) >= malloc_size(ush->in->line)) {
        ush->in->line = realloc(
            ush->in->line, malloc_size(ush->in->line) + strlen(home));
    }
    memmove(ush->in->line + index, home, strlen(home));
    memmove(ush->in->line + index + strlen(home), tmp, strlen(tmp));
    mx_strdel(&tmp);
    mx_strdel(&home);
}

void mx_tilde_expansion(t_ush *ush) {
    bool escape = false;

    for (size_t i = 0; i < strlen(ush->in->line); i++) {
        if (ush->in->line[i] == '\'' || ush->in->line[i] == '\"')
            escape = !escape;
        if (ush->in->line[i] == '~' && !escape) {
            mx_expand_tilde(ush, i, ush->in->line + i + 1);
        }
    }
}

int mx_ush_loop(t_ush *ush) {
    char *line = NULL;
    int status = 0;

    while (!ush->exit) {
        mx_printstr("u$h> ");
        ush->in->line = mx_get_line(ush);
        // tilde expansion
        mx_tilde_expansion(ush);
        mx_create_trees(ush, ush->in->line);
        status = mx_proccess_commands_list(ush);
        mx_clear_trees(ush);
        mx_strdel(&ush->in->line);
    }
    return status;
}
