#ifndef LEITOR_GEO_H
#define LEITOR_GEO_H
#include "../ler_arq/leitor.h"

/**
 * @typedef Chao
 * @brief Ponteiro opaco que representa a coleção de formas geométricas no ambiente do jogo.
 *
 * Funciona como um "handle" para a estrutura de dados que armazena todas as formas
 * criadas a partir do arquivo .geo, ocultando os detalhes da implementação.
 */
typedef void *Chao;

/**
 * @brief Executa os comandos de um arquivo .geo e instancia as formas geométricas.
 *
 * Esta função itera sobre as linhas de comando fornecidas, interpreta cada uma,
 * aloca a memória para a forma geométrica descrita e a armazena na estrutura "Chao".
 *
 * @param dados_arquivo A estrutura contendo as linhas do arquivo .geo a serem processadas.
 * @param caminho_saida O diretório base onde os arquivos de saída (como .svg) serão gerados.
 * @param sufixo_comando Um sufixo opcional a ser adicionado ao nome dos arquivos de saída.
 * @return Um ponteiro do tipo Chao para a coleção de formas criadas, ou NULL em caso de erro.
 */
Chao processar_arquivo_geo(DadosArquivo dados_arquivo, const char *caminho_saida,const char *sufixo_comando);

/**
 * @brief Libera toda a memória associada ao "Chao" e às formas que ele contém.
 *
 * Essencial para a prevenção de vazamentos de memória, esta função deve ser chamada
 * ao final da execução para desalocar todos os recursos criados por `processar_arquivo_geo`.
 *
 * @param chao O ponteiro para a estrutura Chao que deve ser destruída.
 */
void destruir_formas_geo(Chao chao);

#endif