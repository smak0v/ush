#include "ush.h"

static void expand_dollars(t_ush *ush) {
    bool escape = false;

    for (size_t i = 0; i < strlen(ush->in->line); i++) {
        if (ush->in->line[i] == '\'')
            escape = !escape;
        if (ush->in->line[i] == '$' && !escape) {
            if (ush->in->line[i + 1] == '(')
                return;
            mx_expand_dollar(ush, i);
        }
    }
}

static void expand_tildes(t_ush *ush) {
    bool escape = false;

    for (size_t i = 0; i < strlen(ush->in->line); i++) {
        if (ush->in->line[i] == '\'' || ush->in->line[i] == '\"')
            escape = !escape;
        if (ush->in->line[i] == '~' && !escape) {
            if (i - 2 >= 0 && ush->in->line[i - 2] == '\\'
                && isspace(ush->in->line[i - 1])) {
                continue;
            }
            if (i != 0 && !isspace(ush->in->line[i - 1])
                && ush->in->line[i - 1] != '`'
                && ush->in->line[i - 1] != '(') {
                return;
            }
            mx_expand_tilde(ush, i);
        }
    }
}

void mx_expansions(t_ush *ush) {
    expand_dollars(ush);
    expand_tildes(ush);
}
