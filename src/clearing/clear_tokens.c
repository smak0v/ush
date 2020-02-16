#include "ush.h"

void mx_clear_tokens(t_dll **tokens) {
    t_token *token = NULL;

    while (tokens && *tokens) {
        token = (t_token *)(*tokens)->data;
        mx_strdel(&token->data);
        free((*tokens)->data);
        mx_dll_pop_front(tokens);
    }
}
