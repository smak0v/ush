#include "ush.h"

void mx_init_signal(void) {
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void mx_signal_dfl(void) {
    signal(SIGINT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

//============================================================================
void mx_susspend_process(void) {
    // mx_printint_endl(getpid());
    // kill(getpid(), SIGSTOP);
}

void mx_init_custom_signals(void) {
    signal(SIGTSTP, mx_susspend_process);
}
//============================================================================