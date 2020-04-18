#include "ush.h"

void mx_print_echo(char **flags, char **arguments) {
    if (!arguments || !(*arguments))
        return;

    mx_printstr(arguments[0]);
    
    for (int i = 1; arguments[i]; i++) {
        mx_printstr(" ");
        mx_printstr(arguments[i]);
    }

    if (!mx_check_flag(flags, 'n'))
        mx_printchar('\n');
}
