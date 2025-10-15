/*
    This module contains the functions that will
    be used to handle the arguments
    that will be passed to the program

*/
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

/**
 * @brief Obtém o sufixo do comando a partir dos argumentos da linha de comando.
 *
 * Esta função analisa os argumentos fornecidos (argc e argv) e retorna uma string
 * contendo o sufixo do comando, se houver. O sufixo geralmente representa parâmetros
 * adicionais ou modificadores do comando principal.
 *
 * @param argc Número de argumentos fornecidos na linha de comando.
 * @param argv Vetor de strings contendo os argumentos da linha de comando.
 * @return Ponteiro para uma string contendo o sufixo do comando, ou NULL se não houver sufixo.
 */
    char *get_command_suffix(int argc, char *argv[]);

#endif