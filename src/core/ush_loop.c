#include "ush.h"

int mx_ush_loop(t_ush *ush) {
    size_t size = 1;
    char *line = malloc(size * sizeof(char *));
    int status = 0;

    while (1) {
        mx_printstr("u$h> ");
        getline(&line, &size, stdin);
        line[mx_strlen(line) - 1] = '\0';
        mx_create_trees(ush, line);
        status = mx_proccess_commands_list(ush);
        mx_clear_trees(ush);
        mx_strdel(&line);
    }
    return status;
}
