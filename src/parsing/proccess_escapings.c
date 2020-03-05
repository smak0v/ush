#include "ush.h"

char *mx_proccess_escapings(char *line) {
    int len = mx_strlen(line);
    char *new_line = NULL;

    for (int i = 0, j = -1; i < len; ) {
        if (line[i] == '\\' && (i + 1) < len && !mx_isspace(line[i + 1])) {
            new_line = realloc(new_line, mx_strlen(new_line) + 2);
            new_line[++j] = line[i + 1];
            new_line[j + 1] = '\0';
            i += 2;
        }
        else {
            new_line = realloc(new_line, mx_strlen(new_line) + 2);
            new_line[++j] = line[i];
            new_line[j + 1] = '\0';
            ++i;
        }
    }
    mx_strdel(&line);
    return new_line;
}
