#include "ush.h"

char *mx_get_line(t_ush *ush) {
    char *line = mx_memalloc(1024);
    long key = 0;
    int i = 0;

    mx_enable_input_mode(ush);
    while (key != 10) {
        read(0, &key, 8);
        if ((key >= 32 && key <= 127)) {
            line[i++] = key;
            mx_printchar(key);
        }
        // if (key == LEFT || key == RIGHT || key == UP || key == DOWN) {
        //     if (key == LEFT)
        //         tputs(tgetstr("le", NULL), 1, mx_printchar);
        //     if (key == RIGHT)
        //         tputs(tgetstr("nd", NULL), 1, mx_printchar);
        // }
        if (key != 10)
            key = 0;
    }
    mx_printstr("\n");
    mx_disable_input_mode(ush);
    mx_add_cmd(&(ush->history), mx_create_hist_node(line));
    return line;
}
