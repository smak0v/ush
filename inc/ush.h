#pragma once

// Includes
#include "libmx.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <termcap.h>

// Constants
#define USH_TOK_BUFFSIZE 64
#define USH_TOK_DELIM " \t\r\n\a"
#define USH_TREE_END_STATUS 999

// Macroses

// Structures
typedef struct s_ush {
    t_dll *trees;
}              t_ush;

typedef struct s_token {
    char *data;
    int type;
} t_token;

// Fucntions
// Core
int mx_ush_loop(t_ush *ush);
int mx_proccess_commands_list(t_ush *ush);
int mx_traverse_and_execute_tree(t_tree *tree, t_ush *ush);
int mx_execute(char **args, t_ush *ush);
int mx_launch(char **args, t_ush *ush);

// Utils
t_dll *mx_split_token(char *token);
char **mx_split_cmd(char *cmd);
void mx_create_trees(t_ush *ush, char *line);
void mx_create_tree(t_dll *sub_tokens, t_tree **leaf);
void mx_print_inorder_tree(t_tree *tree);

// Signals

// Builtins
int mx_ush_cd(char **args, t_ush *ush);
int mx_ush_pwd(char **args, t_ush *ush);
int mx_ush_env(char **args, t_ush *ush);
int mx_ush_echo(char **args, t_ush *ush);
int mx_ush_exit(char **args, t_ush *ush);

// Data clearing
void mx_clear_tokens(t_dll **tokens);
void mx_clear_trees(t_ush *ush);
