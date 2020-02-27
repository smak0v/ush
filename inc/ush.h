#pragma once

// Includes
#include "libmx.h"

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <termcap.h>
#include <termios.h>

// Constants
#define MX_USH_TOK_BUFFSIZE 64
#define MX_USH_TOK_DELIM " \t\r\n\a"

#define MX_ENV_FLAGS "iPu"
#define MX_CD_FLAGS "sP"
#define MX_PWD_FLAGS "LP"
#define MX_WHICH_FLAGS "as"
#define MX_ECHO_FLAGS "neE"

#define RIGHT       4414235
#define LEFT        4479771
#define UP          4283163
#define DOWN        4348699
#define ESC         27
#define BACKSPACE   127
#define ENTER       10

// Macroses

// Structures
typedef struct s_hist t_hist;
typedef struct s_ush t_ush;
typedef struct s_token t_token;
typedef struct s_env t_env;
typedef struct s_input t_input;

struct s_input {
    size_t win_x;
    size_t cur_x;
    size_t cur_y;
    char *line;
    int key;
    size_t winsize;
};

struct s_ush {
    t_dll *trees;
    t_hist *history;
    t_hist *current;
    struct termios savetty;
    t_list *env;
    t_input *in;
};


struct s_env {
    bool i;
    char *P;
    char *u;
    char **env;
    char *utility;
    char error;
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

typedef enum e_builtins {
    env,
    cd,
    pwd,
    which,
    echo,
    ext
}            t_blt;

// Functions
// Core
int mx_ush_loop(t_ush *ush);
int mx_proccess_commands_list(t_ush *ush);
void mx_traverse_and_execute_tree(t_tree *tree, t_ush *ush, int *status);
int mx_execute(char *cmd, t_ush *ush);
void mx_execute_piped(char **args, char **piped_args);
int mx_launch(char **args);
char *mx_get_line(t_ush *ush);
t_ush *mx_init_shell();
void mx_init_terminal_data();
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
int mx_printnbr(int i);
t_list *mx_create_env_list(char **environ);

// Signals

// Builtins
char **mx_store_flags(char **argv);
char **mx_store_files(char **argv);
int mx_flags_validation(char **flags, t_blt builtin);
int mx_ush_cd(char **args, t_ush *ush);
int mx_ush_pwd(char **args, t_ush *ush);
int mx_ush_env(char **args, t_ush *ush);
int mx_ush_echo(char **args, t_ush *ush);
int mx_ush_exit(char **args, t_ush *ush);

    // CD

    // ENV
int mx_env(char **flags, char **arguments, t_ush *ush);
t_env *mx_parse_env(char **args);
void mx_env_illegal_option(char illegal_option);

// Data clearing
void mx_clear_tokens(t_dll **tokens);
void mx_clear_trees(t_ush *ush);
