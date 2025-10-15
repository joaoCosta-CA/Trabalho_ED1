#include "argumentos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Retorna o valor associado a uma opção no formato -opt valorOpcao
char *get_option_value(int argc, char *argv[], char *opt_name) {
    for (int i = 1; i < argc - 1; ++i) {
        if (argv[i][0] == '-' && strcmp(argv[i] + 1, opt_name) == 0) {
            return argv[i + 1];
        }
    }
    return NULL;
}

// Retorna o sufixo do comando (último argumento que não começa com '-')
char *get_command_suffix(int argc, char *argv[]) {
    char *suffix = NULL;
    int suffix_count = 0;

    for (int i = 1; i < argc; ++i) {
        // Ignora pares -opt valor
        if (argv[i][0] == '-') {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                ++i; // pula o valor da opção
            }
        } else {
            suffix = argv[i];
            ++suffix_count;
        }
    }

    if (suffix_count == 1) {
        return suffix;
    } else if (suffix_count > 1) {
        printf("Erro: Mais de um sufixo\n");
        exit(1);
    }
    return NULL;
}
