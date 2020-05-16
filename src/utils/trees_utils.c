#include "ush.h"

void mx_right_branch(t_dll *tmp, t_tree **leaf) {
    t_token *token = (t_token *)tmp->data;
    t_token *next_token = (t_token *)tmp->next->data;

    tmp->next->prev = NULL;
    mx_create_tree(tmp->next, &(*leaf)->right);
    mx_free_token(next_token);
    free(tmp->next);
    tmp->next = NULL;
    mx_free_token(token);
    free(tmp);
    tmp = NULL;
}

void mx_left_branch(t_dll *tmp, t_tree **leaf) {
    tmp->prev->next = NULL;
    while (tmp->prev)
        tmp = tmp->prev;
    mx_create_tree(tmp, &(*leaf)->left);
}

void mx_create_tree(t_dll *sub_tokens, t_tree **leaf) {
    t_dll *tmp_1 = sub_tokens;
    char *data = NULL;
    bool found = false;

    while (tmp_1->next)
        tmp_1 = tmp_1->next;
    while (tmp_1) {
        if (((t_token *)tmp_1->data)->type == 1) {
            found = true;
            data = ((t_token *)tmp_1->data)->data;
            *leaf = mx_create_tree_node(mx_strdup(data));
            mx_right_branch(tmp_1, leaf);
            mx_left_branch(tmp_1, leaf);
            break;
        }
        tmp_1 = tmp_1->prev;
    }
    if (!found && (data = ((t_token *)sub_tokens->data)->data))
        *leaf = mx_create_tree_node(mx_strdup(data));
}

void mx_copy_and_create_tree(char *token, t_dll **trees) {
    t_dll *sub_tokens = mx_split_token(token);
    t_tree *tree = NULL;

    mx_create_tree(sub_tokens, &tree);
    mx_dll_push_back(trees, tree);
    mx_clear_tokens(&sub_tokens);
    mx_strdel(&token);
}
