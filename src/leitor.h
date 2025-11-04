#ifndef LEITOR_H
#define LEITOR_H

#include "fila.h"

/**
 * @file leitor.h
 * @brief Módulo para leitura de arquivos e armazenamento das linhas em uma fila.
 *
 * Este módulo fornece funções para criar uma estrutura que representa um arquivo,
 * contendo seu caminho, nome e as linhas lidas armazenadas em uma fila dinâmica.
 * Permite acessar o caminho e nome do arquivo, bem como iterar pelas linhas carregadas.
 * Também é responsável por liberar corretamente toda a memória alocada.
 */

/**
 * @brief Estrutura que representa um arquivo lido, contendo seu caminho, nome e as linhas em uma fila.
 */
typedef void *DadosArquivo;

/**
 * @brief Cria uma nova instância de DadosArquivo, lendo o conteúdo do arquivo especificado.
 *
 * @param 'caminho_arquivo' será o caminho completo do arquivo a ser lido.
 * @return retorna um ponteiro para DadosArquivo criado, ou NULL em caso de erro.
 */
DadosArquivo dados_arquivo_criar(const char *caminho_arquivo);

/**
 * @brief função que libera a memória alocada para DadosArquivo e todas as linhas armazenadas.
 *
 * @param 'dados' será o ponteiro para DadosArquivo a ser destruído.
 */
void dados_arquivo_destruir(DadosArquivo dados);

/**
 * @brief função que obtém o caminho completo do arquivo armazenado em DadosArquivo.
 *
 * @param 'dados' será o ponteiro para DadosArquivo.
 * @return Ponteiro constante para a string com o caminho do arquivo.
 */
const char *obter_caminho_arquivo(const DadosArquivo dados);

/**
 * @brief função que obtém o nome do arquivo (apenas o nome, sem o caminho).
 *
 * @param 'dados' será o ponteiro para DadosArquivo.
 * @return retorna um ponteiro constante para a string com o nome do arquivo.
 */
const char *obter_nome_arquivo(const DadosArquivo dados);

/**
 * @brief função que obtém a fila contendo as linhas do arquivo.
 *
 * @param 'dados' será o ponteiro para DadosArquivo.
 * @return retorna um ponteiro para Fila contendo as linhas do arquivo.
 */
FILA obter_fila_linhas(const DadosArquivo dados);

#endif // LEITOR_H