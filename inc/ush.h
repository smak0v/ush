#pragma once

// Includes
#include "libmx.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

// Constants
#define USH_TOK_BUFSIZE 64
#define USH_TOK_DELIMS " \t\r\n\a"

// Macroses

// Structures
typedef struct s_ush {
    t_list *history;
}              t_ush;

// Fucntions
// Core
int mx_ush_loop(t_ush *ush, char **envp);
char **mx_split_line(char *line);
int mx_execute(char **args, char **envp);
int mx_launch(char **args);

// Utils
void mx_clear_history(t_list **history);

// Signals

//Builtins
int mx_ush_cd(char **args);
int mx_ush_pwd();
int mx_ush_env(char **envp);
int mx_ush_echo(char **args);
int mx_ush_exit();
