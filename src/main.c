#include "ush.h"

int main(int argc, char **argv, char **envp) {
    int exit_code = 0;
    t_ush *ush = mx_memalloc(sizeof(t_ush));

    argc = 0;
    argv = NULL;
    exit_code = mx_ush_loop(ush, envp);
    // system("leaks ush");
    return exit_code;
}
