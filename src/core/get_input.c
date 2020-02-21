#include "ush.h"

void mx_backspace_key(char *line, size_t *cur_x, size_t *cur_y) {

}

void mx_left_arrow(char *line, size_t *cur_x, size_t *cur_y) {

}

void mx_right_arrow(char *line, size_t *cur_x, size_t *cur_y) {

}

void mx_up_arrow() {

}

void mx_down_arrow() {

}

static void shuffle_text(char *line, size_t *cur_x) {
    for (size_t i = *cur_x; i <= strlen(line); i++)
        line[i] = line[i + 1];
    line[strlen(line)] = 0;
}

static void read_input(long *key, char *line, size_t *cur_x, size_t *cur_y) {
    size_t winsize;

    *key = 0;
    read(0, key, 8);
    mx_init_terminal_data();
    winsize = tgetnum("co");
    if ((*key >= 32 && *key < 127)) {
        line[*cur_x] = *key;
        // tputs(tgetstr("im", NULL), 1, mx_printnbr);
        mx_printchar(*key);
        // tputs(tgetstr("ei", NULL), 1, mx_printnbr);
        ++(*cur_x);
        // if (((*cur_x + 5) / *cur_y) == winsize) {
        //     tputs(tgetstr("do", NULL), 1, mx_printnbr);
        //     tputs(tgetstr("cr", NULL), 1, mx_printnbr);
        //     ++(*cur_y);
        // }
    }
}

static void edit_line(long *key, char *line, size_t *cur_x, size_t *cur_y) {
    // size_t winsize = tgetnum("co");

    if (*key == LEFT && *cur_x != 0) {
        tputs(tgetstr("le", NULL), 1, mx_printnbr);
        --(*cur_x);
    }
    else if (*key == RIGHT && *cur_x < strlen(line)) {
        tputs(tgetstr("nd", NULL), 1, mx_printnbr);
        ++(*cur_x);
    }
    else if (*key == BACKSPACE && *cur_x != 0) {
        tputs(tgetstr("le", NULL), 1, mx_printnbr);
        tputs(tgetstr("dc", NULL), 1, mx_printnbr);
        --(*cur_x);
        shuffle_text(line, cur_x);
    }
}

char *mx_get_line(t_ush *ush) {
    char *line = mx_memalloc(1024);
    long key = 0;
    size_t cur_x = 0;
    size_t cur_y = 1;

    mx_enable_input_mode(ush);
    while (key != ENTER) {
        read_input(&key, line, &cur_x, &cur_y);
        edit_line(&key, line, &cur_x, &cur_y);
    }
    mx_disable_input_mode(ush);
    mx_printstr("\n");
    mx_add_cmd(&(ush->history), mx_create_hist_node(line));
    return line;
}
