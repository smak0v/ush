#include "ush.h"

t_hist *mx_create_hist_node(char *cmd) {
    t_hist *node = mx_memalloc(sizeof(t_hist));

    node->cmd = mx_strdup(cmd);
    return node;
}

void mx_add_cmd(t_hist **hist, t_hist *node) {
    if (!hist || !*hist)
        *hist = node;
    else {
        node->next = *hist;
        (*hist)->prev = node;
        *hist = node;
    }
}
