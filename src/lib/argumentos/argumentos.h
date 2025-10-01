#ifndef ARGUMENTOS_H
#define ARGUMENTOS_H

/*
 * =======================================================================
 * Utilitário para Leitura de Argumentos da Main
 * =======================================================================
 * Declaração de uma função para simplificar a extração de valores
 * passados por linha de comando.
 */

/*
 * Busca o valor correspondente a uma flag específica (opção) nos
 * argumentos da linha de comando.
 *
 * Exemplo de chamada:
 * Se um programa é executado como: ./meu_programa -i entrada.txt -o saida.svg
 * A chamada `get_option(argc, argv, "i")` retornará um ponteiro para "entrada.txt".
 *
 * PARAMETROS:
 * argc: O número de argumentos recebido pela função main.
 * argv: O vetor de strings com os argumentos (recebido pela main).
 * option_name: O nome da flag a ser procurada (ex: "i"), sem o traço '-'.
 *
 * RETORNO:
 * Retorna um ponteiro para a string do valor encontrado.
 * Retorna NULL se a flag não for encontrada ou se não houver um valor após ela.
 */
char* get_option(int argc, char *argv[], char* option_name);

#endif /* ARGUMENTOS_H */