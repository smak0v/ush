#include "ush.h"

static void process_escape(char **arg, char escape, int index) {
    char *tmp = mx_strdup(*arg);
    char *str = *arg;

    str = realloc(str, sizeof(char) * mx_strlen(*arg));
    str[index] = escape;
    mx_strcpy(str + index + 1, &tmp[index + 2]);

    mx_strdel(&tmp);
}

void mx_process_echo_args(char **args) {
    for (int i = 0; args && args[i]; i++)
        for (int j = 0; args[i][j + 1]; j++)
            if (args[i][j] == '\\' && args[i][j + 1] == '\\')
                process_escape(&args[i], '\\', j);
            else if (args[i][j] == '\\' && args[i][j + 1] == 'a')
                process_escape(&args[i], '\a', j);
            else if (args[i][j] == '\\' && args[i][j + 1] == 'b')
                process_escape(&args[i], '\b', j);
            else if (args[i][j] == '\\' && args[i][j + 1] == 'f')
                process_escape(&args[i], '\f', j);
            else if (args[i][j] == '\\' && args[i][j + 1] == 'n')
                process_escape(&args[i], '\n', j);
            else if (args[i][j] == '\\' && args[i][j + 1] == 'r')
                process_escape(&args[i], '\r', j);
            else if (args[i][j] == '\\' && args[i][j + 1] == 't')
                process_escape(&args[i], '\t', j);
            else if (args[i][j] == '\\' && args[i][j + 1] == 'v')
                process_escape(&args[i], '\v', j);
            else if (args[i][j] == '\\' && args[i][j + 1] == 'a')
                process_escape(&args[i], '\a', j);
}

static int calc_len(char **arguments) {
    int counter = 0;

    for (int i = 0; arguments[i]; i++) {
        for (int j = 0; arguments[i][j]; j++) {
            counter++;
            if (arguments[i][j] == '\n')
                counter = 0;
        }
        counter++;
    }
    return counter - 1;
}

void mx_print_echo(t_ush *ush, char **flags, char **arguments) {
    if (!arguments || !(*arguments)) {
        mx_printchar('\n');
        return;
    }

    mx_printstr(arguments[0]);

    for (int i = 1; arguments[i]; i++) {
        mx_printstr(" ");
        mx_printstr(arguments[i]);
    }

    if (!mx_check_flag(flags, 'n'))
        mx_printchar('\n');
    else
        ush->in->chars_after_newline = calc_len(arguments);
}
