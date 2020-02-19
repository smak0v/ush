#include "ush.h"

char **mx_split_cmd(char *cmd) {
    int buff_size = MX_USH_TOK_BUFFSIZE;
    char **args = malloc(buff_size * sizeof(char *));
    int i = -1;
    char *arg = NULL;

    arg = strtok(cmd, MX_USH_TOK_DELIM);
    while (arg) {
        args[++i] = arg;
        if (i >= buff_size) {
            buff_size += MX_USH_TOK_BUFFSIZE;
            args = realloc(args, buff_size * sizeof(char *));
        }
        arg = strtok(NULL, MX_USH_TOK_DELIM);
    }
    args[++i] = NULL;
    return args;
}
