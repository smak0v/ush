#include "ush.h"

static void copy_character(char **args,  int *j, int count, char ch) {
    args[count] = realloc(args[count], mx_strlen(args[count]) + 2);
    args[count][++(*j)] = ch;
    args[count][*j + 1] = '\0';
}

char **mx_split_cmd(char *cmd) {
    int buff_size = MX_USH_TOK_BUFFSIZE;
    char **args = calloc(buff_size, sizeof(char *));
    int count = 0;
    int j = -1;

    for (int i = 0; i < mx_strlen(cmd); ++i) {
        if (!mx_isspace(cmd[i]) && cmd[i] != '\\')
            copy_character(args, &j, count, cmd[i]);
        else if (cmd[i] == '\\' && (i + 1 < mx_strlen(cmd))) {
            copy_character(args, &j, count, cmd[i + 1]);
            ++i;
        }
        else {
            ++count;
            j = -1;
        }
        if (count >= buff_size && (buff_size += MX_USH_TOK_BUFFSIZE))
            args = realloc(args, buff_size * sizeof(char *));
    }
    return args;
}

