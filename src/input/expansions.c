#include "ush.h"

static void expand_dollars(t_ush *ush, char **line) {
    bool escape = false;

    for (size_t i = 0; i < strlen(*line); i++) {
        if ((*line)[i] == '\'' || (*line)[i] == '\"')
            escape = !escape;
        if ((*line)[i] == '$' && !escape) {
            if ((*line)[i + 1] == '(')
                return;
            mx_expand_dollar(ush, line, i);
        }
    }
}

static void expand_tildes(t_ush *ush, char **line) {
    bool escape = false;

    for (size_t i = 0; i < strlen(*line); i++) {
        if ((*line)[i] == '\'' || (*line)[i] == '\"')
            escape = !escape;
        if ((*line)[i] == '~' && !escape) {
            if (i - 2 >= 0 && (*line)[i - 2] == '\\'
                && isspace((*line)[i - 1])) {
                continue;
            }
            if (i != 0 && !isspace((*line)[i - 1])
                && (*line)[i - 1] != '`'
                && (*line)[i - 1] != '(') {
                return;
            }
            mx_expand_tilde(ush, line, i);
        }
    }
}

void mx_expansions(t_ush *ush, char **line) {
    expand_dollars(ush, line);
    expand_tildes(ush, line);
}
