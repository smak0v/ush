#include "ush.h"

int main() {
    int exit_code = 0;
    char **empty = malloc(sizeof(char *) * 2);
    t_ush *ush = mx_init_shell();

    exit_code = mx_ush_loop(ush);

    

    // system("leaks ush");
    return exit_code;
}
