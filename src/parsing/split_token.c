#include "ush.h"

static void copy_part(t_dll **sub_tokens, char **pos, int *len, char *str) {
    t_token *token_1 = malloc(sizeof(t_token));
    t_token *token_2 = malloc(sizeof(t_token));

    token_1->data = mx_strndup(*pos, *len);
    token_1->type = 0;
    mx_dll_push_back(sub_tokens, token_1);
    token_2->data = mx_strdup(str);
    token_2->type = 1;
    mx_dll_push_back(sub_tokens, token_2);
    *pos += *len + mx_strlen(str);
    *len = 0;
}

static void copy_last(t_dll **sub_tokens, char *pos) {
    t_token *token = malloc(sizeof(t_token));

    token->data = mx_strdup(pos);
    token->type = 0;
    mx_dll_push_back(sub_tokens, token);
}

t_dll *mx_split_token(char *token) {
    t_dll *sub_tokens = NULL;
    char *prev_position = token;
    bool quoted = false;

    for (int i = 0, len = 0; i < mx_strlen(token); ++i, ++len) {
        mx_check_quoted(token[i], &quoted);
        if (token[i] == '&' && token[i + 1] == '&' && !quoted && (i += 2))
            copy_part(&sub_tokens, &prev_position, &len, "&&");
        else if (token[i] == '|' && token[i + 1] == '|' && !quoted && (i += 2))
            copy_part(&sub_tokens, &prev_position, &len, "||");
    }
    copy_last(&sub_tokens, prev_position);
    return sub_tokens;
}
