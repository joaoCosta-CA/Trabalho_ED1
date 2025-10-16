#ifndef DISPARADOR_H
#define DISPARADO_H

#include "../fila/fila.h"
#include "../pilha/pilha.h"
#include "../formas/formas.h"
typedef void* Disp;

/**
 * @brief Cria e inicializa um novo objeto do tipo Disparador.
 *
 * Aloca memória para um novo disparador e define seus valores iniciais
 * com base nos parâmetros fornecidos.
 *
 * @param id O identificador único para o novo disparador.
 * @param x A coordenada X inicial do disparador no plano.
 * @param y A coordenada Y inicial do disparador no plano.
 * @return Retorna um ponteiro para o disparador criado (do tipo Disp).
 *         Retorna NULL se a alocação de memória falhar.
 */
Disp criar_disparador(int id, double x, double y);


/**
 * @brief Libera a memória alocada para um objeto Disparador.
 *
 * Garante que todos os recursos associados ao disparador sejam
 * devidamente liberados para evitar vazamentos de memória.
 *
 * @param d O ponteiro para o disparador que deve ser destruído.
 */
void destruir_disparador(Disp d);


/**
 * @brief Atualiza a posição de um disparador existente.
 *
 * Modifica as coordenadas X e Y de um disparador para uma nova posição.
 *
 * @param d O ponteiro para o disparador a ser reposicionado.
 * @param x A nova coordenada X do disparador.
 * @param y A nova coordenada Y do disparador.
 */
void posicionar_disparador(Disp d, double x, double y);


/**
 * @brief Executa a ação de disparo para um determinado disparador.
 *
 * Esta função é responsável por acionar o evento ou a lógica principal
 * associada a um disparador.
 *
 * @param d O ponteiro para o disparador que irá executar a ação.
 */
void disparar_forma(Disp d, double dx, double dy, FILA arena);


void shift_carga(Disp d, char lado, int n);

void rajada_de_disparos(Disp d, char lado, double dx, double dy, double ix, double iy, FILA arena);

void anexar_carregadores(Disp d, PILHA carregador_esq, PILHA carregador_dir);



/*-------------FUNÇÕES GETTERS--------------*/
int disparador_get_id(Disp d);
double disparador_get_x(Disp d);
double disparador_get_y(Disp d);
FormaGeometrica* disparador_get_em_disparo(Disp d);

#endif