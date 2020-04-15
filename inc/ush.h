#pragma once

// Includes
#include "libmx.h"

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <termcap.h>
#include <termios.h>
#include <dirent.h>
#include <pwd.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <uuid/uuid.h>

// Constants
#define MX_IS_EXEC(mode) ((mode) & S_IXUSR)
#define MX_IS_LNK(mode) (((mode) & S_IFMT) == S_IFLNK)

#define MX_BUILTINS_COUNT 16
#define MX_USH_TOK_BUFFSIZE 64
#define MX_USH_TOK_DELIM " \t\r\n\a"
#define MX_DEFAULT_PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

#define MX_ENV_FLAGS "iPu"
#define MX_CD_FLAGS "sP"
#define MX_PWD_FLAGS "LP"
#define MX_WHICH_FLAGS "as"
#define MX_ECHO_FLAGS "neE"

#define MX_RIGHT       4414235
#define MX_LEFT        4479771
#define MX_UP          4283163
#define MX_DOWN        4348699
#define MX_ESC         27
#define MX_BACKSPACE   127
#define MX_ENTER       10
#define MX_CTRL_C      3
#define MX_CTRL_D      4

#define MX_SUCCESS     0
#define MX_FAILURE     1

#define MX_CMD_SUBST_FILE "/.cmd_subst.file"

// Structures
typedef struct s_hist t_hist;
typedef struct s_ush t_ush;
typedef struct s_token t_token;
typedef struct s_env t_env;
typedef struct s_cmd t_cmd;
typedef struct s_input t_input;
typedef struct s_builtins t_builtins;
typedef struct s_process t_process;
typedef struct s_job t_job;
typedef struct s_builtin_job t_builtin_job;
typedef struct s_cmd_subst t_cmd_subst;

struct s_process {
    char **argv;
    int status;
    pid_t pid;
    t_process *next;
};

struct s_job {
    struct termios tmodes;
    char *cmd;
    pid_t pgid;
    int stdin;
    int stdout;
    int stderr;
    t_process *processes;
    t_job *next;
    t_job *prev;
    int index;
};

struct s_builtin_job {
    int index;
    pid_t pgid;
    char *cmd;
};

struct s_builtins {
    int (*mx_ush_cd)(char **, t_ush *);
    int (*mx_ush_pwd)(char **, t_ush *);
    int (*mx_ush_echo)(char **, t_ush *);
    int (*mx_ush_which)(char **, t_ush *);
    int (*mx_ush_exit)(char **, t_ush *);
    int (*mx_ush_bye)(char **, t_ush *);
    int (*mx_ush_env)(char **, t_ush *);
    int (*mx_ush_export)(char **, t_ush *);
    int (*mx_ush_unset)(char **, t_ush *);
    int (*mx_ush_local)(char **, t_ush *);
    int (*mx_ush_jobs)(char **, t_ush *);
    int (*mx_ush_fg)(char **, t_ush *);
    int (*mx_ush_history)(char **, t_ush *);
    int (*mx_ush_return)(char **, t_ush *);
    int (*mx_ush_true)(char **, t_ush *);
    int (*mx_ush_false)(char **, t_ush *);
};

struct s_input {
    size_t win_x;
    size_t cur_x;
    size_t cur_y;
    char *line;
    int key;
    size_t winsize;
};

struct s_ush {
    t_job *suspended;
    bool delete_suspended;
    t_dll *trees;
    t_hist *history;
    t_hist *current;
    t_input *in;
    char **builtins;
    char **env;
    char **export;
    char **local_variables;
    char **hidden;
    struct termios savetty;
    int *exit;
    int exit_code;
    pid_t pgid;
    bool cmd_subst;
    char *cmd_substs_file;
};

struct s_cmd {
    char **args;
};

struct s_env {
    bool i;
    char *P;
    char *u;
    char **name_val;
    char **util;
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

typedef enum e_defaults {
    OLDPWD,
    PWD,
    SHLVL,
    PATH,
    TERM,
    HOME
}            t_def;


// Functions
// Core
int mx_ush_loop(t_ush *ush);
int mx_process_commands_list(t_ush *ush);
void mx_traverse_and_execute_tree(t_tree *tree, t_ush *ush, int *status);
t_ush *mx_init_shell(void);
void mx_init_terminal_data(void);
void mx_enable_input_mode(t_ush *ush);
void mx_disable_input_mode(t_ush *ush);

// Parsing
char *mx_proccess_escapings(char *line);
t_dll *mx_split_token(char *token);
char **mx_split_cmd(char *cmd);

// Utils
void mx_create_trees(t_ush *ush, char *line);
void mx_create_tree(t_dll *sub_tokens, t_tree **leaf);
void mx_print_inorder_tree(t_tree *tree);
int mx_printnbr(int i);
void mx_choose_error(char **args, char **env);
void mx_set_default(t_ush *ush, int *not_found);
char **mx_process_home(char **arr);
char **mx_split_key_value(char *str);
int mx_check_identifier_validity(char **strarr, int ravno);
int mx_check_identifier_validity_unset(char *str, int ravno);
char **mx_add_var(char **export, char *keyword);
char *mx_build_pwd_str(void);
char *mx_get_pwd(void);
char *mx_getenv(char **env, char *key);
char *mx_get_homepath(void);
void mx_overwrite_strarr_value(char ***arr, char *key, char *value);
char *mx_build_key_value_str(char *key, char *value);
int mx_check_duplicate(char ***array, char *key);
char **mx_safe_split(char *arg);
char **mx_create_tmp_env(t_ush *ush, char ***args);
void mx_setup_underscore_env_var(t_ush *ush, char *arg);
int mx_check_flag(char **flags, char flag);
bool mx_is_builtin(char *name, t_ush *ush);
t_builtins *mx_init_builtins(void);

// Signals
void mx_ignore_signals(void);
void mx_default_signals(void);

// Input
char *mx_get_line(t_ush *ush);
void mx_shuffle_text(t_input *in);
void mx_add_cmd(t_hist **hist, t_hist *node);
t_hist *mx_create_hist_node(char *cmd);
void mx_expand_tilde(t_ush *ush, size_t index, char *postfix);
void mx_expand_dollar(t_ush *ush, size_t index, char *postfix);
void mx_expansions(t_ush *ush);
void mx_arrow_left(t_input *in);
void mx_arrow_right(t_input *in);
void mx_arrow_up(t_ush *ush);
void mx_arrow_down(t_ush *ush);
void mx_backspace(t_input *in);
void mx_init_line(t_ush *ush);
void mx_update_cursor(t_input *in);
void mx_cursor_to_promt(t_input *in);

// Job control system
int get_jobs_max_index(t_job *jobs);
t_job *mx_create_job(char *cmd);
t_job *mx_copy_job(t_job *job);
void mx_push_front_job(t_job **jobs, t_job *job);
void mx_delete_job(t_job **job);
int mx_get_job_index(t_job *jobs, t_job *job);
int mx_suspended_jobs_list_size(t_job *suspended_jobs);
t_process *create_process(char *cmd);
t_process *mx_create_processes(char *cmd);
t_process *mx_copy_processes(t_process *processes);
void push_back_proccess(t_process **processes, t_process *process);
void mx_delete_processes(t_process **processes);
int mx_launch_job(t_job *job, t_ush *ush, char **env);
int mx_launch_proccess(pid_t pgid, t_process *procces, int *fd, t_ush *ush);
int mx_launch_simple_builtin(t_ush *ush, char **argv);
int mx_wait_and_check_status(t_ush *ush, t_job *job, int status, pid_t pid);
t_job *mx_sort_jobs(t_job *head);

// Command substitutions
void mx_command_substitutions(t_ush *ush);
char *mx_get_cmd_substs_filename(void);
void mx_change_line(t_ush *ush, char **new_cmd_subst, int start, int end);

// Builtins
char **mx_store_flags(char **argv);
char **mx_store_files(char **argv);
char *mx_flags_validation(char **flags, t_blt builtin);
int mx_ush_cd(char **args, t_ush *ush);
int mx_ush_pwd(char **args, t_ush *ush);
int mx_ush_env(char **args, t_ush *ush);
int mx_ush_echo(char **args, t_ush *ush);
int mx_ush_exit(char **args, t_ush *ush);
int mx_ush_export(char **args, t_ush *ush);
int mx_ush_unset(char **args, t_ush *ush);
int mx_ush_local(char **args, t_ush *ush);
int mx_ush_which(char **args, t_ush *ush);
int mx_ush_history(char **args, t_ush *ush);
int mx_ush_return(char **args, t_ush *ush);
int mx_ush_true(char **args, t_ush *ush);
int mx_ush_false(char **args, t_ush *ush);
void mx_invalid_identifier(char *cmd, char *identifier);

    // CD
int mx_cd(t_ush *ush, char **flags, char *destination);
char *mx_build_path(char *pwd, char *fname);
int mx_cd_not_a_directory_error(char **delstr, char *destination);
int mx_cd_no_such_file_or_dir(char **delstr, char *destination);
int mx_cd_invalid_option(char *option);
char mx_check_link(char **path, char *full_path);
char *mx_build_logical_path(char *pwd, char *dest, char *realpath);

    // ENV
int mx_env(t_env *env, t_ush *ush);
t_env *mx_parse_env(char **args);
void mx_env_illegal_option(char illegal_option);
void mx_option_requires_an_argument(char option);
void mx_env_janitor(t_env **env_struct);

    // EXPORT
void mx_export(char **arguments, t_ush *ush, int *status);
int mx_process_duplicate(t_ush *ush, char *arg, char *key);
void mx_export_invalid_option(char *option);

    // UNSET
void mx_unset(t_ush *ush, char **arg, int *status);
void mx_unset_invalid_option(char *option);

    // WHICH
char **mx_which(t_ush *ush, char **flags, char **args, int *status);
void mx_which_invalid_option(char *option);
void mx_which_usage_error(int *status);
char **mx_get_split_path(t_ush *ush);

    //ECHO
void mx_print_echo(char **flags, char **arguments);
char **mx_echo_parse_flags(char **args);
char **mx_echo_parse_args(char **args);

    // EXIT
short int mx_exit(char **args, int *exit);

    // JOBS
int mx_ush_jobs(char **args, t_ush *ush);
void mx_have_suspended_jobs_error(void);

    // FG
int mx_ush_fg(char **args, t_ush *ush);
int mx_no_job_control_error(void);
void mx_no_such_job_error(char *name);
void mx_ambiguous_job_spec_error(char *name);
void mx_invalid_option_error(char *name);
bool mx_job_is_number(char *job_arg);
int mx_get_job_index_by_number(char *job_arg, t_job *jobs);
int mx_get_job_index_by_name(char *job_arg, t_job *jobs);

// Data clearing
void mx_clear_tokens(t_dll **tokens);
void mx_clear_trees(t_ush *ush);
int mx_clean_data(char **tmp_env);
void mx_reset_env_and_clean_data(int (**builtin_func)(char **, t_ush *));

// Errors
void mx_proccess_start_error(char *process_name);
void mx_command_not_found_error(char *command_name);
void mx_no_such_file_or_directory(char *cmd);
