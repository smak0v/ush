#include "ush.h"

int main() {
    int exit_code = 0;
    t_ush *ush = mx_init_shell();
    char line[MX_ARG_MAX];

    if (!isatty(STDIN_FILENO)) {
        fgets(line, sizeof(line), stdin);
        ush->in->line = mx_strdup(line);
        mx_ush_core(ush);
        return ush->exit_code;
    }
    exit_code = mx_ush_loop(ush);
    // system("leaks ush");
    return exit_code;
}
