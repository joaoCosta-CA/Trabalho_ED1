#include "argumentos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_option_value(int argc, char *argv[], char *opt_name) {
    for (int i = 1; i < argc - 1; ++i) {
        if (argv[i][0] == '-' && strcmp(argv[i] + 1, opt_name) == 0) {
            return argv[i + 1];
        }
    }
    return NULL;
}
