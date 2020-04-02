#include "ush.h"

static void copy_character(char **args,  int *j, int count, char ch) {
    args[count] = realloc(args[count], mx_strlen(args[count]) + 2);
    args[count][++(*j)] = ch;
    args[count][*j + 1] = '\0';
}

static void copy_quoted_string(char **args, char *cmd, size_t *j, char ch) {
    size_t len = strlen(cmd);
    int counter = 0;

    for (size_t i = 0; i < len; ++i, ++counter) {
        if (cmd[i] != ch)
            continue;
        if (cmd[i] == ch && cmd[i - 1] != '\\') {
            *j += counter + 2;
            *args = mx_strndup(cmd, counter);
        }
    }
}

static void skip_spaces(int *count, int *j, size_t *i, char *cmd) {
    ++(*count);
    *j = -1;
    while (mx_isspace(cmd[*i]))
        ++(*i);
    --(*i);
}

char **mx_split_cmd(char *cmd) {
    int buff_size = MX_USH_TOK_BUFFSIZE;
    char **args = calloc(buff_size, sizeof(char *));
    int count = 0;
    int j = -1;

    for (size_t i = 0; i < strlen(cmd); ++i) {
        if (cmd[i] == '"' && cmd[i - 1] != '\\' && (i + 1 < strlen(cmd)))
            copy_quoted_string(&args[count++], &cmd[i + 1], &i, '"');
        else if (cmd[i] == '\'' && cmd[i - 1] != '\\' && (i + 1 < strlen(cmd)))
            copy_quoted_string(&args[count++], &cmd[i + 1], &i, '\'');
        else if (!mx_isspace(cmd[i]) && cmd[i] != '\\')
            copy_character(args, &j, count, cmd[i]);
        else if (cmd[i] == '\\' && (i + 1 < strlen(cmd)) && (++i))
            copy_character(args, &j, count, cmd[i]);
        else
            skip_spaces(&count, &j, &i, cmd);
        if (count >= buff_size && (buff_size += MX_USH_TOK_BUFFSIZE))
            args = realloc(args, buff_size * sizeof(char *));
    }
    return args;
}
