#include "ush.h"

static void is_closed_quotes(char *line, char ch, size_t *i, bool *is_closed) {
    if (line[*i] == ch) {
        *is_closed = false;
        for (size_t j = *i + 1; j < strlen(line); ++j)
            if (line[j] == ch) {
                *is_closed = true;
                *i = j;
                break;
            }
    }
}

bool mx_is_empty_line(char *line) {
    for (size_t i = 0; i < strlen(line); ++i)
        if (!mx_isspace(line[i]))
            return false;
    return true;
}

bool mx_is_closed_quotes(char *line) {
    bool is_closed = true;

    for (size_t i = 0; i < strlen(line); ) {
        is_closed_quotes(line, '"', &i, &is_closed);
        is_closed_quotes(line, '\'', &i, &is_closed);
        ++i;
    }
    return is_closed;
}
