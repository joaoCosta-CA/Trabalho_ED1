#ifndef CARREGADOR_H
#define CARREGADOR_H

#include "leitor_geo.h"
#include "pilha.h"

/**
 * @brief Ponteiro opaco para o tipo Carregador.
 *
 * Define Carregador como um ponteiro opaco (void*) para ocultar a
 * implementação concreta do carregador. A manipulação do objeto deve
 * ser feita apenas através das funções públicas declaradas neste cabeçalho.
 */
typedef void *Carregador;

// --- Funções do TAD Carregador ---

/**
 * @brief Cria um novo carregador identificado por um ID.
 *
 * Aloca e inicializa um objeto Carregador associando-o ao identificador
 * fornecido. A implementação deve garantir que o carregador comece em
 * estado vazio pronto para receber formas.
 *
 * @param id Identificador do carregador (valor fornecido pelo chamador).
 * @return Carregador Instância do carregador criada.
 *
 * @pre O identificador fornecido deve ser válido no contexto da aplicação.
 * @note O comportamento em caso de falha de alocação depende da implementação.
 */
Carregador criar_carregador(int id);

/**
 * @brief Destrói um carregador e libera os recursos associados.
 *
 * Libera toda a memória e recursos internos usados pelo carregador. Após
 * a chamada, o carregador não deve mais ser usado.
 *
 * @param c Carregador a ser destruído.
 *
 * @pre O parâmetro c deve referenciar um carregador válido previamente criado.
 * @note Se o carregador contiver formas, a função deve cuidar da liberação
 *       ou do descarte adequado dessas formas conforme a política do projeto.
 */
void destruir_carregador(Carregador c);

/**
 * @brief Obtém o identificador associado a um carregador.
 *
 * Retorna o ID que foi atribuído ao carregador na sua criação.
 *
 * @param c Carregador cujo ID será retornado.
 * @return int Identificador do carregador.
 *
 * @pre O parâmetro c deve referenciar um carregador válido.
 */
int carregador_get_id(Carregador c);

/**
 * @brief Adiciona (municia) uma forma geométrica no carregador.
 *
 * Insere a forma fornecida na estrutura interna do carregador para uso
 * posterior. Se não for possível armazenar a forma (por exemplo, falta
 * de espaço), a operação não terá efeito.
 *
 * @param c Carregador onde a forma será inserida.
 * @param forma FormaGeometrica a ser adicionada ao carregador.
 *
 * @pre O parâmetro c deve referenciar um carregador válido; forma deve
 *      ser uma instância válida de FormaGeometrica.
 * @note A função não retorna erro; o chamador não deve assumir que a forma
 *       foi armazenada caso o carregador esteja cheio.
 */
void carregador_municia_forma(Carregador c, FormaGeometrica forma);

/**
 * @brief Retira e retorna a próxima forma do carregador.
 *
 * Remove uma forma armazenada no carregador e a retorna ao chamador.
 * A ordem de retirada segue a política definida pela implementação (por
 * exemplo, FIFO, LIFO, ou outra).
 *
 * @param c Carregador de onde a forma será retirada.
 * @return FormaGeometrica A forma removida. Se o carregador estiver vazio,
 *                         o valor retornado indicará ausência de forma
 *                         (conforme a definição de FormaGeometrica no projeto).
 *
 * @pre O parâmetro c deve referenciar um carregador válido.
 */
FormaGeometrica carregador_retira_forma(Carregador c);

/**
 * @brief Verifica se o carregador está vazio.
 *
 * Indica se o carregador não contém nenhuma forma armazenada.
 *
 * @param c Carregador a ser verificado.
 * @return int Retorna 1 se o carregador estiver vazio, 0 caso contrário.
 *
 * @pre O parâmetro c deve referenciar um carregador válido.
 */
int carregador_esta_vazio(Carregador c);

/**
 * @brief Retorna um ponteiro para a pilha interna do carregador.
 * @param c O carregador.
 * @return Um ponteiro para a PILHA.
 */
PILHA carregador_get_pilha(Carregador c);

#endif