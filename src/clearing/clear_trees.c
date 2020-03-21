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

void mx_clear_trees(t_ush *ush) {
    t_dll *trees = ush->trees;
    t_tree *tree = NULL;

    while (trees) {
        tree = (t_tree *)trees->data;
        clear_tree(&tree);
        mx_dll_pop_front(&trees);
    }
    ush->trees = NULL;
}
