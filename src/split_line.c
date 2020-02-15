#include "ush.h"

char **mx_split_line(char *line) {
    int i = 0;
    int buffsize = USH_TOK_BUFSIZE;
    char **tokens = malloc(buffsize * sizeof(char *));
    char *token = strtok(line, USH_TOK_DELIMS);

    while (token) {
        tokens[i++] = token;
        if (i >= buffsize) {
            buffsize += USH_TOK_BUFSIZE;
            tokens = realloc(tokens, buffsize * sizeof(char *));
        }
        token = strtok(NULL, USH_TOK_DELIMS);
    }
    tokens[i] = NULL;
    return tokens;
}
