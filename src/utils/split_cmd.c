#include "ush.h"

char **mx_split_cmd(char *cmd) {
    int buff_size = USH_TOK_BUFFSIZE;
    char **args = malloc(buff_size * sizeof(char *));
    int i = -1;
    char *arg = NULL;

    arg = strtok(cmd, USH_TOK_DELIM);
    while (arg) {
        args[++i] = arg;
        if (i >= buff_size) {
            buff_size += USH_TOK_BUFFSIZE;
            args = realloc(args, buff_size * sizeof(char *));
        }
        arg = strtok(NULL, USH_TOK_DELIM);
    }
    args[++i] = NULL;
    return args;
}
