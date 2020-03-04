#include "ush.h"

static char **build_export_args(char *key, char *value) {
    char **export = mx_memalloc(sizeof(char *) * 3);

    export[0] = mx_strdup("export");
    export[1] = mx_strjoin(key, value);
    export[2] = NULL;

    return export;
}

int mx_cd(t_ush *ush, char **flags, char **args) {
    char **export = NULL;

    if (!args) {
        char *home = mx_getenv(ush->hidden, "HOME");

        chdir(home);
        export = build_export_args("PWD=", home);
        mx_ush_export(export, ush);
    }


}
