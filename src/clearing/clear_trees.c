#include "ush.h"

static void clear_tree(t_tree **tree) {
    char *data = NULL;

    if (!(*tree))
        return;
    clear_tree(&(*tree)->left);
    data = (char *)(*tree)->data;
    mx_strdel(&data);
    clear_tree(&(*tree)->right);
    free(*tree);
    *tree = NULL;
}

void mx_clear_trees(t_dll **trees) {
    t_dll *trees_ptr = *trees;
    t_tree *tree = NULL;

    while (trees_ptr) {
        tree = (t_tree *)trees_ptr->data;
        clear_tree(&tree);
        mx_dll_pop_front(&trees_ptr);
    }
    *trees = NULL;
}
