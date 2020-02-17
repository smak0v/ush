#include "ush.h"

int mx_traverse_and_execute_tree(t_tree *tree, t_ush *ush) {
    int status = 0;
    char **args = NULL;

    if (!tree)
        return USH_TREE_END_STATUS;
    status = mx_traverse_and_execute_tree(tree->left, ush);
    args = mx_split_cmd(tree->data);
    mx_execute(args, ush);
    status = mx_traverse_and_execute_tree(tree->right, ush);
    if (status == USH_TREE_END_STATUS)
        status = 1;
    return status;
}
