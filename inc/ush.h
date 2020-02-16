#pragma once

// Includes
#include "libmx.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <termcap.h>

// Constants

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
int mx_execute(char **args);
int mx_launch(char **args);

// Utils
t_dll *mx_split_token(char *token);
void mx_create_trees(t_ush *ush, char *line);
void mx_create_tree(t_dll *sub_tokens, t_tree **leaf);
void mx_print_inorder_tree(t_tree *tree);

// Signals

// Builtins
int mx_ush_cd(char **args);
int mx_ush_pwd();
int mx_ush_env(char **args);
int mx_ush_echo(char **args);
int mx_ush_exit();

// Data clearing
void mx_clear_tokens(t_dll **tokens);
