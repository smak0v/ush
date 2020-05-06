#include "ush.h"

void mx_check_quoted(char line_i, bool *quoted) {
    static char ch = '-';

    if (line_i == '"' && ch == '-') {
        ch = '"';
        *quoted = !*quoted;
    }
    else if (line_i == '"' && ch == '"') {
        ch = '-';
        *quoted = !*quoted;
    }
    else if (line_i == '\'' && ch == '-') {
        ch = '\'';
        *quoted = !*quoted;
    }
    else if (line_i == '\'' && ch == '\'') {
        ch = '-';
        *quoted = !*quoted;
    }
}
