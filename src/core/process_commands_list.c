#include "ush.h"

int mx_process_commands_list(t_ush *ush, t_dll **trees) {
    t_dll *trees_ptr = *trees;
    t_dll *tree = trees_ptr;
    int status = 0;

    while (tree) {
        mx_traverse_and_execute_tree((t_tree *)tree->data, ush, &status);
        tree = tree->next;
    }
    mx_clear_trees(trees);
    return status;
}
