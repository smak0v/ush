#include "ush.h"

void mx_init_terminal_data() {
    char term_buffer[2048];
    char *termtype = "xterm-256color";
    int success = 0;

    if (termtype == 0)
        mx_terminate("Specify a terminal type: \'export TERM=<termtype>\'.");
    success = tgetent(term_buffer, termtype);
    if (success < 0)
        mx_terminate("Could not access the termcap data base.");
    if (success == 0)
        mx_terminate("Terminal type is not defined.");
}

void mx_enable_input_mode(t_ush *ush) {
    struct termios tty;

    !isatty(0) ? mx_terminate("stdin not terminal") : (void)0;
    tcgetattr(0, &tty);
    ush->savetty = tty;
    tty.c_lflag &= ~(ICANON|ECHO|ISIG|BRKINT|ICRNL
        |INPCK|ISTRIP|IXON|OPOST|IEXTEN);
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VDSUSP] = _POSIX_VDISABLE;
    tty.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &tty);
}

void mx_disable_input_mode(t_ush *ush) {
    tcsetattr(0, TCSANOW, &(ush->savetty));
}
