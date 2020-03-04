#include "ush.h"

static void print_numeric_error(char *arg) {
    mx_print_error("ush: exit: ");
    mx_print_error(arg);
    mx_print_error_endl(": numeric argument required");
}

static void print_many_args_error(void) {
    mx_print_error_endl("ush: exit: too many arguments");
}

static unsigned char calc_code(long long arg) {
    unsigned char code = (unsigned char)arg;

    return code;
}

static short int check_args(char **args) {
    long long exit_arg = atoll(*args);

    // Peer to peer for a better solution
    if (exit_arg < -9223372036854775807 || exit_arg > 9223372036854775806)
        return -1;

    for (int i = 0; args[0][i]; i++) {
        if (i == 0 && args[0][i] == '-')
            continue;
        if (!mx_isdigit(args[0][i])) {
            return -1;
        }
    }

    if (args[1])
        return -2;

    return (short int)calc_code(exit_arg);
}

short int mx_exit(char **args, int *exit) {
    short int check_arg = check_args(args);

    if (check_arg == -1) {
        print_numeric_error(*args);
        return 255;
    }
    else if (check_arg == -2) {
        print_many_args_error();
        *exit = 0;
        return 1;
    }
    else
        return check_arg;
}
