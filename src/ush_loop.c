#include "ush.h"

int mx_ush_loop(t_ush *ush, char **envp) {
    size_t size = 1;
    char *line = (char *)malloc(size);
    char **args = NULL;
    int status = 1;

    while (status) {
        mx_printstr("u$h> ");
        getline(&line, &size, stdin);
        mx_push_front(&ush->history, mx_strdup(line));
        args = mx_split_line(line);
        status = mx_execute(args, envp);
        mx_strdel(&line);
    }
    mx_clear_history(&ush->history);
    return status;
}
