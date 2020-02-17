#include "ush.h"

// static bool check_multiline(char *line, size_t size) {
//     for (int i = size; i >= 0; --i)
//         if (line[i] == '\\')
//             return true;
//     return false;
// }

int mx_ush_loop(t_ush *ush) {
    size_t size = 1;
    char *line = malloc(size);
    int status = 1;

    while (status) {
        mx_printstr("u$h> ");
        getline(&line, &size, stdin);
        line[mx_strlen(line) - 1] = '\0';
        // Multiline input
        // while (check_multiline(line, size)) {
        //     mx_printstr("> ");
        //     getline(&line, &size, stdin);
        //     line[mx_strlen(line) - 1] = '\0';
        // }
        mx_create_trees(ush, line);
        status = mx_proccess_commands_list(ush);
        // mx_clear_trees(ush);
        mx_strdel(&line);
    }
    return status;
}
