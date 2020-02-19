#pragma once

// Includes
#include "libmx.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <termcap.h>
#include <fcntl.h>
#include <termios.h>

// Constants
#define MX_USH_TOK_BUFFSIZE 64
#define MX_USH_TOK_DELIM " \t\r\n\a"

# define RIGHT		4414235
# define LEFT		4479771
# define UP			4283163
# define DOWN		4348699
# define ESC		27
#define BACKSPACE 127


// Macroses

// Structures
typedef struct s_hist t_hist;
typedef struct s_ush t_ush;
typedef struct s_token t_token;

struct s_ush {
    t_dll *trees;
    t_hist *history;
    struct termios savetty;

};

struct s_token {
    char *data;
    int type;
};

struct s_hist {
    char *cmd;
    t_hist *next;
    t_hist *prev;
};

// Functions
// Core
int mx_ush_loop(t_ush *ush);
int mx_proccess_commands_list(t_ush *ush);
void mx_traverse_and_execute_tree(t_tree *tree, t_ush *ush, int *status);
int mx_execute(char **args, t_ush *ush);
int mx_launch(char **args);
char *mx_get_line(t_ush *ush);
t_ush *mx_init_shell();
void mx_enable_input_mode(t_ush *ush);
void mx_disable_input_mode(t_ush *ush);

// Utils
t_dll *mx_split_token(char *token);
char **mx_split_cmd(char *cmd);
void mx_create_trees(t_ush *ush, char *line);
void mx_create_tree(t_dll *sub_tokens, t_tree **leaf);
void mx_print_inorder_tree(t_tree *tree);
void mx_add_cmd(t_hist **hist, t_hist *node);
t_hist *mx_create_hist_node(char *cmd);

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
