#ifndef LEITOR_GEO_H
#define LEITOR_GEO_H
#include "../ler_arq/leitor.h"
#include "../fila/fila.h"
#include "../formas/formas.h"
#include <stdio.h>

/**
 * @typedef Chao
 * @brief Ponteiro opaco que representa a coleção de formas geométricas no ambiente do jogo.
 *
 * Funciona como um "handle" para a estrutura de dados que armazena todas as formas
 * criadas a partir do arquivo .geo, ocultando os detalhes da implementação.
 */
typedef void *Chao;

typedef void* FormaGeometrica;

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

/**
 * @brief Retorna a fila principal de formas que estão no "chão".
 * Esta função concede acesso à fila para que outros módulos possam
 * remover formas dela (ex: comando 'lc').
 * @param chao O ponteiro opaco para o estado do leitor_geo.
 * @return A FILA contendo as formas geométricas.
 */
FILA leitor_geo_get_fila_principal(Chao chao);

/**
 * @brief Obtém o tipo de uma forma geométrica (Círculo, Retângulo, etc.).
 * @param forma O ponteiro opaco para a forma.
 * @return O tipo da forma, conforme o enum ShapeType.
 */
ShapeType forma_get_tipo(FormaGeometrica forma);


/**
 * @brief Obtém o ponteiro para os dados específicos da forma (ex: a struct do Círculo).
 * @param forma O ponteiro opaco para a forma.
 * @return Um ponteiro void* para os dados específicos da forma.
 */
void* forma_get_dados(FormaGeometrica forma);

/**
 * @brief Abre um arquivo SVG no caminho especificado e escreve o cabeçalho.
 * @param caminho_completo O caminho completo do arquivo .svg a ser criado.
 * @return Um ponteiro para o arquivo (FILE*) aberto, ou NULL em caso de erro.
 */
FILE* svg_iniciar(const char* caminho_completo);

/**
 * @brief Desenha todas as formas contidas no "Chao" em um arquivo SVG já aberto.
 * @param arquivo_svg O ponteiro do arquivo retornado por svg_iniciar.
 * @param chao O estado do "chão" contendo as formas a serem desenhadas.
 */
void svg_desenhar_chao(FILE* arquivo_svg, Chao chao);

/**
 * @brief Escreve a tag de fechamento do SVG e fecha o arquivo.
 * @param arquivo_svg O ponteiro do arquivo a ser finalizado.
 */
void svg_finalizar(FILE* arquivo_svg);

int forma_get_id(FormaGeometrica forma);
void destruir_forma_completa(FormaGeometrica forma);

// Funções para obter coordenadas (necessárias para anotações)
double forma_get_x(FormaGeometrica forma); // Retorna a coordenada X principal (centro, canto, âncora)
double forma_get_y(FormaGeometrica forma); // Retorna a coordenada Y principal

// Funções para cores (necessárias para clonagem/alteração)
const char* forma_get_cor_preenchimento(FormaGeometrica forma);
const char* forma_get_cor_borda(FormaGeometrica forma);
void forma_set_cor_borda(FormaGeometrica forma, const char* nova_cor);

// Função de clonagem
FormaGeometrica forma_clonar(FormaGeometrica forma_original, int* proximo_id);

// Função para obter o maior ID usado no arquivo .geo
int leitor_geo_get_max_id(Chao chao);

#endif