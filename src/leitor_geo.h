#ifndef LEITOR_GEO_H
#define LEITOR_GEO_H

#include "leitor.h"
#include "fila.h"
#include "pilha.h"
#include "formas.h"
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
 * @brief função que executa os comandos de um arquivo .geo e instancia as formas geométricas.
 *
 * Esta função itera sobre as linhas de comando fornecidas, interpreta cada uma,
 * aloca a memória para a forma geométrica descrita e a armazena na estrutura "Chao".
 *
 * @param 'dados_arquivo' será a estrutura contendo as linhas do arquivo .geo a serem processadas.
 * @param 'caminho_saida' será o diretório base onde os arquivos de saída (como .svg) serão gerados.
 * @param 'sufixo_comando' será um sufixo opcional a ser adicionado ao nome dos arquivos de saída.
 * 
 * @return retorna um ponteiro do tipo Chao para a coleção de formas criadas, ou NULL em caso de erro.
 */
Chao processar_arquivo_geo(DadosArquivo dados_arquivo, const char *caminho_saida,const char *sufixo_comando);

/**
 * @brief função que libera toda a memória associada ao "Chao" e às formas que ele contém.
 *
 * Essencial para a prevenção de vazamentos de memória, esta função deve ser chamada
 * ao final da execução para desalocar todos os recursos criados por `processar_arquivo_geo`.
 *
 * @param 'chao' será o ponteiro para a estrutura Chao que deve ser destruída.
 */
void destruir_formas_geo(Chao chao);

/**
 * @brief função que retorna a fila principal de formas que estão no "chão".
 * 
 * Esta função concede acesso à fila para que outros módulos possam
 * remover formas dela (ex: comando 'lc').
 * 
 * @param 'chao' será o ponteiro opaco para o estado do leitor_geo.
 * @return retorna a FILA contendo as formas geométricas.
 */
FILA leitor_geo_get_fila_principal(Chao chao);

/**
 * @brief função que obtém o tipo de uma forma geométrica (Círculo, Retângulo, etc.).
 * 
 * @param 'forma' será o ponteiro opaco para a forma.
 * @return retorna o tipo da forma, conforme o enum ShapeType.
 */
ShapeType forma_get_tipo(FormaGeometrica forma);


/**
 * @brief função que obtém o ponteiro para os dados específicos da forma (ex: a struct do Círculo).
 * 
 * @param 'forma' será o ponteiro opaco para a forma.
 * @return retorna um ponteiro void* para os dados específicos da forma.
 */
void* forma_get_dados(FormaGeometrica forma);

/**
 * @brief função que abre um arquivo SVG no caminho especificado e escreve o cabeçalho.
 * 
 * @param 'caminho_completo' será o caminho completo do arquivo .svg a ser criado.
 * @return retorna um ponteiro para o arquivo (FILE*) aberto, ou NULL em caso de erro.
 */
FILE* svg_iniciar(const char* caminho_completo);

/**
 * @brief função que desenha todas as formas contidas no "Chao" em um arquivo SVG já aberto.
 * 
 * @param 'arquivo_svg' será o ponteiro do arquivo retornado por svg_iniciar.
 * @param 'chao' será o estado do "chão" contendo as formas a serem desenhadas.
 */
void svg_desenhar_chao(FILE* arquivo_svg, Chao chao);

/**
 * @brief função que escreve a tag de fechamento do SVG e fecha o arquivo.
 * 
 * @param 'arquivo_svg' será o ponteiro do arquivo a ser finalizado.
 */
void svg_finalizar(FILE* arquivo_svg);

/**
 * @brief função que obtém o identificador associado a uma forma geométrica.
 *
 * Retorna o ID que identifica a forma passada como argumento. O ID é
 * normalmente usado para referenciação e busca de propriedades específicas
 * da forma.
 *
 * @param 'forma' será a instância (ou ponteiro) da forma geométrica cujo ID será obtido.
 * 
 * @return retorna o valor do identificador da forma. Em caso de forma inválida
 *         (por exemplo, NULL ou estrutura sem ID definido) a função
 *         retorna um valor indicativo de erro (por exemplo, -1).
 * 
 * @pre  o parâmetro 'forma' deve representar uma forma válida; caso contrário o valor
 *       de retorno indica erro.
 */
int forma_get_id(FormaGeometrica forma);

/**
 * @brief função que libera todos os recursos associados a uma forma geométrica.
 *
 * Esta função deve desalocar toda a memória e recursos internos usados pela
 * forma (dados geométricos, strings, listas internas, etc.), garantindo que
 * não haja vazamento de memória.
 *
 * @param 'forma' será a instância (ou ponteiro) da forma geométrica a ser destruída.
 *
 * @post  recursos associados à forma foram liberados e não devem ser usados
 *        novamente.
 */
void destruir_forma_completa(FormaGeometrica forma);


/**
 * @brief função que retorna a coordenada X da forma geométrica.
 *
 * @param 'forma' será a estrutura FormaGeometrica devidamente inicializada.
 * @return retorna a coordenada X da forma (valor em double).
 */
double forma_get_x(FormaGeometrica forma);

/**
 * @brief função que retorna a coordenada Y da forma geométrica.
 *
 * @param 'forma' será a estrutura FormaGeometrica devidamente inicializada.
 * @return retorna a coordenada Y da forma (valor em double).
 */
double forma_get_y(FormaGeometrica forma);


/**
 * @brief função que retorna a cor de preenchimento da forma.
 *
 * @param 'forma' será a instância válida de FormaGeometrica (não-NULL).
 *
 * @return retorna um ponteiro para uma string NUL-terminada que representa a cor de preenchimento
 *         (por exemplo nome ou código da cor). O ponteiro aponta para memória gerida
 *         internamente pela forma; o chamador NÃO deve modificar nem liberar essa string.
 *         a validade do ponteiro está vinculada ao ciclo de vida da forma e pode ser
 *         alterada por operações que modifiquem a forma.
 */
const char* forma_get_cor_preenchimento(FormaGeometrica forma);

/**
 * @brief função que retorna a cor da borda da forma.
 *
 * @param 'forma' será a instância válida de FormaGeometrica (não-NULL).
 *
 * @return retorna um ponteiro para uma string NUL-terminada que representa a cor da borda.
 *         o ponteiro aponta para memória interna da forma; o chamador NÃO deve
 *         modificar nem liberar essa string. a validade do ponteiro depende do
 *         ciclo de vida e do estado da forma.
 */
const char* forma_get_cor_borda(FormaGeometrica forma);

/**
 * Define a cor da borda da forma.
 *
 * @param 'forma' será a instância válida de FormaGeometrica (não-NULL).
 * @param nova_cor  String NUL-terminada com o nome ou código da nova cor (deve ser não-NULL).
 *
 * @behavior a função atualiza a cor da borda da forma para o valor fornecido.
 *           implementações devem copiar o conteúdo de 'nova_cor' para armazenamento
 *           interno ou documentar claramente a política de ownership; após a chamada,
 *           o chamador pode modificar ou liberar a string passada.
 */
void forma_set_cor_borda(FormaGeometrica forma, const char* nova_cor);


/**
 * @brief função que cria uma cópia (clone) de uma FormaGeometrica.
 *
 * @param 'forma_original' será a FormaGeometrica a ser clonada. A forma original não é modificada.
 * @param 'proximo_id' será o ponteiro para um inteiro usado para atribuir um novo identificador ao clone. Se 'proximo_id' for != NULL, o clone recebe como id o valor apontado por 'proximo_id' e o inteiro apontado é incrementado (*proximo_id)++ para preparar o próximo id disponível. Se 'proximo_id' for NULL, o clone preserva o id da forma_original.
 * 
 * @return retorna uma nova FormaGeometrica contendo a cópia profunda da forma_original.
 */
FormaGeometrica forma_clonar(FormaGeometrica forma_original, int* proximo_id);


/**
 * @brief função que retorna o maior identificador (ID) entre as formas presentes no Chao.
 *
 * Percorre a fila principal de formas contida em 'chao' e retorna o maior ID
 * atualmente em uso. útil para atribuição de novos IDs ou para consultas de
 * consistência.
 *
 * @param 'chao' será o ponteiro opaco para o estado do leitor_geo.
 * @return retorna o maior ID encontrado (valor >= 0). Retorna -1 se 'chao' for NULL ou
 *         se não houver formas registradas.
 */
int leitor_geo_get_max_id(Chao chao);


/**
 * @brief Obtém um ponteiro para a pilha de gerenciamento de memória.
 * 
 * @param 'chao' será o ponteiro opaco para o estado do leitor_geo.
 * @return retorna a PILHA usada para gerenciamento de memória.
 */
PILHA leitor_geo_get_pilha_gestao(Chao chao);

#endif