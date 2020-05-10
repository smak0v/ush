#include "ush.h"

static void shell_and_operator(t_tree *tree, t_ush *ush, int *status) {
    if (*status > 0 || *status < 0)
        return;
    mx_traverse_and_execute_tree(tree->right, ush, status);
}

static void shell_or_operator(t_tree *tree, t_ush *ush, int *status) {
    if (!*status)
        return;
    mx_traverse_and_execute_tree(tree->right, ush, status);
}

static void process_cmd_substs_and_expansions(t_ush *ush, t_tree **tree) {
    t_tree *tree_ptr = *tree;
    char *line = (char *)tree_ptr->data;

    mx_expansions(ush, &line);
    (*tree)->data = line;
    if (!ush->cmd_subst) {
        mx_command_substitutions(ush, &line, 0);
        ush->cmd_subst = false;
        (*tree)->data = line;
    }
}

void mx_prepare_subline_and_launch_job(t_ush *ush, t_tree *tree, int *status) {
    t_job *job = NULL;

    process_cmd_substs_and_expansions(ush, &tree);
    job = mx_create_job(tree->data);
    *status = mx_launch_job(job, ush);
    mx_delete_job(&job);
}

void mx_traverse_and_execute_tree(t_tree *tree, t_ush *ush, int *status) {
    char **args = NULL;

    if (!tree)
        return;
    mx_traverse_and_execute_tree(tree->left, ush, status);
    args = mx_split_cmd(tree->data);
    if (args && *args) {
        if (!mx_strcmp(args[0], "&&"))
            shell_and_operator(tree, ush, status);
        else if (!mx_strcmp(args[0], "||"))
            shell_or_operator(tree, ush, status);
        else {
            mx_prepare_subline_and_launch_job(ush, tree, status);
            mx_traverse_and_execute_tree(tree->right, ush, status);
        }
    }
    mx_del_strarr(&args);
}
