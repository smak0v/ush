#include "ush.h"

void mx_expansions(t_ush *ush) {
    bool escape = false;

    for (size_t i = 0; i < strlen(ush->in->line); i++) {
        if (ush->in->line[i] == '\'' || ush->in->line[i] == '\"')
            escape = !escape;
        if (ush->in->line[i] == '$' && !escape) {
            mx_expand_dollar(ush, i, ush->in->line + i + 1);
        }
    }
    for (size_t i = 0; i < strlen(ush->in->line); i++) {
        if (ush->in->line[i] == '\'' || ush->in->line[i] == '\"')
            escape = !escape;
        if (ush->in->line[i] == '~' && !escape) {
            if (i - 2 >= 0 && ush->in->line[i - 2] == '\\'
                && isspace(ush->in->line[i - 1])) {
                    continue;
                }
            mx_expand_tilde(ush, i, ush->in->line + i + 1);
        }
    }
}
