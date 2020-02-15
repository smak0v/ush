#include "ush.h"

static void copy_part(t_list **sub_tokens, char **pos, int *len, char *str) {
    char *tmp = mx_strndup(*pos, *len);

    mx_push_back(sub_tokens, mx_strtrim(tmp));
    mx_strdel(&tmp);
    mx_push_back(sub_tokens, mx_strdup(str));
    *pos += *len + mx_strlen(str);
    *len = 0;
}

static void copy_last(t_list **sub_tokens, char *pos) {
    char *tmp = mx_strdup(pos);

    mx_push_back(sub_tokens, mx_strtrim(tmp));
    mx_strdel(&tmp);
}

t_list *mx_split_token(char *token) {
    t_list *sub_tokens = NULL;
    char *prev_position = token;

    for (int i = 0, len = 0; i < mx_strlen(token); ++i, ++len)
        if (token[i] == '&' && token[i + 1] == '&' && (i += 2))
            copy_part(&sub_tokens, &prev_position, &len, "&&");
        else if (token[i] == '|' && token[i + 1] == '|' && (i += 2))
            copy_part(&sub_tokens, &prev_position, &len, "||");
        else if (token[i] == '>' && token[i + 1] == '>' && (i += 2))
            copy_part(&sub_tokens, &prev_position, &len, ">>");
        else if (token[i] == '<' && token[i + 1] == '<' && (i += 2))
            copy_part(&sub_tokens, &prev_position, &len, "<<");
        else if (token[i] == '|' && token[i + 1] != '|' && ++i)
            copy_part(&sub_tokens, &prev_position, &len, "|");
        else if (token[i] == '>' && ++i)
            copy_part(&sub_tokens, &prev_position, &len, ">");
        else if (token[i] == '<' && ++i)
            copy_part(&sub_tokens, &prev_position, &len, "<");
    copy_last(&sub_tokens, prev_position);
    return sub_tokens;
}
