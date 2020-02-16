#include "ush.h"

void mx_print_inorder_tree(t_tree *tree) {
    if (!tree)
        return;
    mx_print_inorder_tree(tree->left);
    mx_printstr_endl(tree->data);
    mx_print_inorder_tree(tree->right);
}
