#include "ush.h"

static t_tree *creat_tree(char *token) {
    t_list *sub_tokens = mx_split_token(token);
    t_tree *tree = mx_memalloc(sizeof(t_tree));

    t_list *node = sub_tokens;
    while (node) {
        mx_printstr_endl(node->data);
        node = node->next;
    }
    tree->cmd = mx_strdup(token);
    return tree;
}

void mx_create_trees(t_ush *ush, char *line) {
    char *token = strtok(line, ";");

    while (token) {
        mx_push_back(&ush->trees, (void *)creat_tree(token));
        token = strtok(NULL, ";");
    }
}
