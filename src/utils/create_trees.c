#include "ush.h"

static void free_token(t_token *token) {
    mx_strdel(&token->data);
    free(token);
    token = NULL;
}

static void right_branch(t_dll *tmp, t_tree **leaf) {
    t_token *token = (t_token *)tmp->data;
    t_token *next_token = (t_token *)tmp->next->data;

    tmp->next->prev = NULL;
    mx_create_tree(tmp->next, &(*leaf)->right);
    free_token(next_token);
    free(tmp->next);
    tmp->next = NULL;
    free_token(token);
    free(tmp);
    tmp = NULL;
}

static void left_branch(t_dll *tmp, t_tree **leaf) {
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
            right_branch(tmp_1, leaf);
            left_branch(tmp_1, leaf);
            break;
        }
        tmp_1 = tmp_1->prev;
    }
    if (!found && (data = ((t_token *)sub_tokens->data)->data))
        *leaf = mx_create_tree_node(mx_strdup(data));
}

void mx_create_trees(t_ush *ush, t_dll **trees, char *line) {
    char *token = NULL;
    t_dll *sub_tokens = NULL;
    t_tree *tree = NULL;

    if (mx_is_empty_line(line))
        return;
    if (!mx_is_closed_quotes(line)) {
        mx_print_error("ush: multiline input not supported\n");
        return;
    }
    token = strtok(line, ";");
    while (token) {
        sub_tokens = mx_split_token(token);
        mx_create_tree(sub_tokens, &tree);
        mx_dll_push_back(trees, tree);
        mx_clear_tokens(&sub_tokens);
        token = strtok(NULL, ";");
    }
}
