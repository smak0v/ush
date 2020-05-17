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

bool mx_is_in_cmd_subs(char *line, int index) {
    --index;
    for (int i = index; i >= 0; --i) {
        if (line[i] == '`')
            return false;
        else if (line[i] == '(' && (i - 1 >= 0) && line[i - 1] == '$')
            return false;
    }
    return true;
}
