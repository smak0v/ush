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

bool mx_check_path(char *line, size_t start_index) {
    char *user_path = NULL;
    char *path = NULL;
    struct stat pstat;
    size_t end_index = strlen(line);

    for (size_t i = start_index; i < strlen(line); i++)
        if (isspace(line[i])) {
            if (i - 1 > 0 && line[i - 1] == '\\')
                continue;
            end_index = i;
        }
    user_path = strndup(line + start_index + 1, end_index);
    path = mx_strjoin("/Users/", user_path);
    mx_strdel(&user_path);
    if (stat(path, &pstat) < 0)
        mx_strdel(&path);
    return path;
}

void mx_expand_tilde(t_ush *ush, size_t index, char *postfix) {
    char *home = NULL;
    char *line = ush->in->line;
    char *tmp = mx_strdup(line + index + 1);

    if (index != 0 && !isspace(line[index - 1]))
        return;
    if (strcmp(postfix, "+") == 0)
        return;  // home = $PWD
    else if (strcmp(postfix, "-") == 0)
        return;  // home = $OLDPWD
    else if (!postfix[0] || isspace(postfix[0]) || postfix[0] == '/')
        home = mx_get_home(ush);
    else
        home = mx_check_path(line, index) ? strdup("/Users/") : strdup("~");
    if (strlen(home) + strlen(line) >= malloc_size(line))
        ush->in->line = realloc(line, malloc_size(line) + strlen(home));
    memmove(line + index, home, strlen(home));
    memmove(line + index + strlen(home), tmp, strlen(tmp));
    mx_strdel(&tmp);
    mx_strdel(&home);
}

// создать папку input, закинуть туда все, что связано с инпутом и вынести все приколы отсюда
// в файл expancions.c
void mx_expansions(t_ush *ush) {
    bool escape = false;

    for (size_t i = 0; i < strlen(ush->in->line); i++) {
        if (ush->in->line[i] == '\'' || ush->in->line[i] == '\"')
            escape = !escape;
        if (ush->in->line[i] == '~' && !escape) {
            if (i - 2 >= 0 && ush->in->line[i - 2] == '\\'
                && isspace(ush->in->line[i - 1])) {
                    continue;
                }
            mx_expand_tilde(ush, i, ush->in->line + i + 1);
        }
        if (ush->in->line[i] == '$' && !escape) {
            // mx_expand_dollar(ush, i, ush->in->line + i + 1);
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
        mx_expansions(ush);
        mx_create_trees(ush, ush->in->line);
        status = mx_proccess_commands_list(ush);
        mx_clear_trees(ush);
        mx_strdel(&ush->in->line);
    }
    return status;
}
