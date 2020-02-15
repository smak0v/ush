#include "ush.h"

int mx_ush_loop(t_ush *ush) {
    size_t size = 1;
    char *line = (char *)malloc(size);
    int status = 1;

    while (status) {
        mx_printstr("u$h> ");
        getline(&line, &size, stdin);
        line[mx_strlen(line) - 1] = '\0';
        mx_create_trees(ush, line);
        // while (ush->trees) {
        //     mx_printstr_endl(ush->trees->data);
        //     ush->trees = ush->trees->next;
        // }
        // if (mx_strcmp(line, "\n\0")) {
        //     mx_push_front(&ush->history, mx_strdup(line));
        //     args = mx_split_line(line);
        //     status = mx_execute(args, envp);
        // }
        mx_strdel(&line);
    }
    mx_clear_history(&ush->history);
    return status;
}
