#pragma once

// Includes
#include "libmx.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

// Constants
#define USH_TOK_BUFSIZE 64
#define USH_TOK_DELIMS " \t\r\n\a"

// Macroses

// Structures
typedef struct s_ush {
    t_list *history;
    t_list *trees;
}              t_ush;

typedef struct s_tree {
    struct s_tree *left;
    struct s_tree *right;
    char *cmd;
}              t_tree;

// Fucntions
// Core
int mx_ush_loop(t_ush *ush);
char **mx_split_line(char *line);
int mx_execute(char **args);
int mx_launch(char **args);

// Utils
void mx_clear_history(t_list **history);
void mx_create_trees(t_ush *ush, char *line);
t_list *mx_split_token(char *token);

// Signals

//Builtins
int mx_ush_cd(char **args);
int mx_ush_pwd();
int mx_ush_env(char **args);
int mx_ush_echo(char **args);
int mx_ush_exit();
