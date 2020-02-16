#include "ush.h"

int mx_ush_loop(t_ush *ush) {
    size_t size = 1;
    char *line = malloc(size);
    int status = 1;

    while (status) {
        mx_printstr("u$h> ");
        getline(&line, &size, stdin);
        line[mx_strlen(line) - 1] = '\0';
        mx_create_trees(ush, line);
        // TODO (signals, processes)
        mx_strdel(&line);
    }
    return status;
}
