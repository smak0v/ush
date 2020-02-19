#include "ush.h"

static void init_terminal_data() {
    char term_buffer[2048];
    char *termtype = getenv("TERM");
    int success;

    if (termtype == 0)
        mx_terminate("Specify a terminal type: \'export TERM=<termtype>\'.");
    success = tgetent(term_buffer, termtype);
    if (success < 0)
        mx_terminate("Could not access the termcap data base.");
    if (success == 0)
        mx_terminate("Terminal type `%s' is not defined.");
}

void mx_enable_input_mode(t_ush *ush) {
    struct termios tty;

	init_terminal_data();
    !isatty(0) ? mx_terminate("stdin not terminal") : (void)0;
    tcgetattr(0, &tty);
    ush->savetty = tty;
    tty.c_lflag &= ~(ICANON | ECHO);
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VDSUSP] = _POSIX_VDISABLE;
    tty.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &tty);
}

void mx_disable_input_mode(t_ush *ush) {
    tcsetattr(0, TCSANOW, &(ush->savetty));
}
