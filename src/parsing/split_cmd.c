#include "ush.h"

static void copy_character(char **args,  int *j, int count, char ch) {
    args[count] = realloc(args[count], mx_strlen(args[count]) + 2);
    args[count][++(*j)] = ch;
    args[count][*j + 1] = '\0';
}

static bool copy_double_quoted_string(char **args, int *count, char *cmd,
                                      int *j) {
    int len = mx_strlen(cmd);
    int counter = 0;

    for (int i = 0; i < len; ++i, ++counter) {
        if (cmd[i] != '"')
            continue;
        if (cmd[i] == '"' && cmd[i - 1] != '\\') {
            *j += counter + 2;
            args[*count] = mx_strndup(cmd, counter);
            ++(*count);
            return true;
        }
    }
    return false;
}

static bool copy_quoted_string(char **args, int *count, char *cmd, int *j) {
    int len = mx_strlen(cmd);
    int counter = 0;

    for (int i = 0; i < len; ++i, ++counter) {
        if (cmd[i] != '\'')
            continue;
        if (cmd[i] == '\'' && cmd[i - 1] != '\\') {
            *j += counter + 2;
            args[*count] = mx_strndup(cmd, counter);
            ++(*count);
            return true;
        }
    }
    return false;
}

char **mx_split_cmd(char *cmd) {
    int buff_size = MX_USH_TOK_BUFFSIZE;
    char **args = calloc(buff_size, sizeof(char *));
    int count = 0;
    int j = -1;

    for (int i = 0; i < mx_strlen(cmd); ++i) {
        if (cmd[i] == '"' && cmd[i - 1] != '\\' && (i + 1 < mx_strlen(cmd)))
            if (!copy_double_quoted_string(args, &count, &cmd[i + 1], &i)) {
                mx_del_strarr(&args);
                mx_print_error("ush: multiline input not supported\n");
                return NULL;
            }
            else
                continue;
        else if (cmd[i] == '\'' && cmd[i - 1] != '\\' && (i + 1 < mx_strlen(cmd)))
            if (!copy_quoted_string(args, &count, &cmd[i + 1], &i)) {
                mx_del_strarr(&args);
                mx_print_error("ush: multiline input not supported\n");
                return NULL;
            }
            else
                continue;
        else if (!mx_isspace(cmd[i]) && cmd[i] != '\\')
            copy_character(args, &j, count, cmd[i]);
        else if (cmd[i] == '\\' && (i + 1 < mx_strlen(cmd)) && (++i))
            copy_character(args, &j, count, cmd[i]);
        else {
            ++count;
            j = -1;
        }
        if (count >= buff_size && (buff_size += MX_USH_TOK_BUFFSIZE))
            args = realloc(args, buff_size * sizeof(char *));
    }
    return args;
}
