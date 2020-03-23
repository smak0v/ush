#include "ush.h"

static void parse_flags(t_echo *setup, char **args) {
    setup->escape = 1;
}

t_echo *mx_echo_parsing(char **args) {
    t_echo *setup = (t_echo *)mx_memalloc(sizeof(t_echo));
    mx_print_strarr(args, " ");
    
    if (args[0][0] == '-') {
        parse_flags(setup, args);
    }

    return setup;
}
