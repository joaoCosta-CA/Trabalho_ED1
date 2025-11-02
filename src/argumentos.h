#ifndef ARGUMENTOS_H
#define ARGUMENTOS_H

/**
 * @brief Obtém o valor associado a uma opção específica dos argumentos da linha de comando.
 *
 * Esta função procura na lista de argumentos fornecida por uma opção que corresponda a `opt_name`
 * e retorna o valor que a segue. Se a opção não for encontrada ou não tiver um valor associado,
 * a função retorna NULL.
 *
 * @param argc Número de argumentos da linha de comando.
 * @param argv Vetor de strings contendo os argumentos da linha de comando.
 * @param opt_name Nome da opção a ser procurada (ex: "--file").
 * @return Ponteiro para a string do valor associado à opção, ou NULL se não encontrado.
 */
    char *get_option_value(int argc, char *argv[], char *opt_name);
#endif