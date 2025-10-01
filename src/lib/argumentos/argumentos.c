#include "argumentos.h"
#include <string.h>  

/*
 * Implementação da função get_option.
 */
char* get_option(int argc, char *argv[], char* option_name) {
    // validação para evitar falhas caso argv ou option_name sejam nulos.
    if (!argv || !option_name) {
        return NULL;
    }

    // O laço começa em 1 para pular o nome do programa (argv[0]).
    // A condição 'i < argc - 1' garante que sempre exista um argv[i + 1] para ser retornado.
    for (int i = 1; i < argc - 1; i++) {
        // Verifica se o argumento atual começa com '-'.
        // Compara o resto do argumento (a partir do segundo caractere) com option_name.
        if (argv[i][0] == '-' && strcmp(&argv[i][1], option_name) == 0) {
            // Se encontrou a opção, retorna o próximo argumento como seu valor.
            return argv[i + 1];
        }
    }

    // Se o laço terminar sem encontrar a opção, retorna NULL.
    return NULL;
}