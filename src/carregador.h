#ifndef CARREGADOR_H
#define CARREGADOR_H

#include "leitor_geo.h"
#include "pilha.h"

/**
 * @brief definição de um ponteiro opaco para o tipo Carregador.
 *
 * Define Carregador como um ponteiro opaco (void*) para ocultar a
 * implementação concreta do carregador. A manipulação do objeto deve
 * ser feita apenas através das funções públicas declaradas neste cabeçalho.
 */
typedef void *Carregador;

/**
 * @brief função que cria um novo carregador identificado por um ID.
 *
 * @param 'id' será o identificador do carregador que será criado.
 * @return retorna um ponteiro para o carregador criado ou NULL caso a alocação de memória falhe
 *
 * @pre O identificador fornecido deve ser válido no contexto da aplicação.
 * @note O comportamento em caso de falha de alocação depende da implementação.
 */
Carregador criar_carregador(int id);

/**
 * @brief função que destrói um carregador e libera os recursos associados.
 *
 * @param 'c' será o carregador que será destruído.
 *
 * @pre o parâmetro 'c' deve referenciar um carregador válido previamente criado.
 * @note se o carregador contiver formas, a função deve cuidar da liberação
 *       ou do descarte adequado dessas formas conforme a política do projeto.
 */
void destruir_carregador(Carregador c);

/**
 * @brief Obtém o identificador associado a um carregador.
 *
 * @param 'c' será o carregador cujo ID será retornado.
 * @return retorna o identificador do carregador.
 *
 * @pre o parâmetro 'c' deve referenciar um carregador válido.
 */
int carregador_get_id(Carregador c);

/**
 * @brief função que adiciona (municia) uma forma geométrica no carregador.
 *
 * @param 'c' será o carregador onde a forma será inserida.
 * @param 'forma' será a forma geométrica a ser adicionada ao carregador.
 *
 * @pre o parâmetro 'c' deve referenciar um carregador válido; forma deve
 *      ser uma instância válida de FormaGeometrica.
 * @note a função não retorna erro; o chamador não deve assumir que a forma
 *       foi armazenada caso o carregador esteja cheio.
 */
void carregador_municia_forma(Carregador c, FormaGeometrica forma);

/**
 * @brief função que retira e retorna a próxima forma do carregador.
 *
 * @param 'c' será o carregador de onde a forma será retirada.
 * @return retorna a forma geométrica removida ou NULL caso o carregador esteja vazio
 *
 * @pre o parâmetro 'c' deve referenciar um carregador válido.
 */
FormaGeometrica carregador_retira_forma(Carregador c);

/**
 * @brief função que verifica se o carregador está vazio.
 *
 * @param 'c' será o carregador a ser verificado.
 * @return retorna 1 se o carregador estiver vazio, 0 caso contrário.
 *
 * @pre o parâmetro 'c' deve referenciar um carregador válido.
 */
int carregador_esta_vazio(Carregador c);

/**
 * @brief função que retorna um ponteiro para a pilha interna do carregador.
 * @param 'c' será o carregador cuja pilha interna será retornada.
 * @return retorna um ponteiro para a PILHA ou NULL caso o carregador seja nulo
 */
PILHA carregador_get_pilha(Carregador c);

/**
 * @brief Inverte a ordem das formas no carregador.
 * @param 'c' será o carregador cujas formas serão invertidas.
 */
void carregador_inverter(Carregador c);

#endif