#include "ush.h"

int mx_proccess_commands_list(t_ush *ush) {
    t_dll *tree = ush->trees;
    int status = 0;

    while (tree) {
        status = mx_traverse_and_execute_tree((t_tree *)tree->data, ush);
        tree = tree->next;
    }
    return status;
}
