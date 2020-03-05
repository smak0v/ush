#include "ush.h"

int main() {
    // mx_printint_endl(getpid());
    int exit_code = 0;
    t_ush *ush = mx_init_shell();

    exit_code = mx_ush_loop(ush);
    // system("leaks ush");
    return exit_code;
}
