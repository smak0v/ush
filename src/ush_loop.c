#include "ush.h"

int ush_loop() {
    size_t size = 1;
    char *line = (char *)malloc(size);
    char **args = NULL;
    int status = 0;

    while (1) {
        mx_printstr("u$h> ");
        getline(&line, &size, stdin);
        args = split_line(line);
        status = execute(args);
        mx_strdel(&line);
    }
    return status;
}
