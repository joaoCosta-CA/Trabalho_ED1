#ifndef DISPADOR_H
#define DISPADOR_H

#include "fila.h"
#include "formas.h"
#include "carregador.h"

// Ponteiro opaco para o Disparador
typedef void* Disp;

/**
 * @brief função que cria e inicializa um novo disparador.
 *
 * @param 'id' será o identificador único do disparador.
 * @param 'x' será a coordenada X da posição inicial do disparador.
 * @param 'y' será a coordenada Y da posição inicial do disparador.
 * @return retorna um objeto Disp inicializado.
 */
Disp criar_disparador(int id, double x, double y);

/**
 * @brief Destrói um disparador e libera os recursos associados.
 *
 * @param 'disp' será o disparador que será destruído.
 *
 * @pre o parâmetro 'disp' deve referenciar um disparador válido previamente criado.
 */
void destruir_disparador(Disp disp);

/**
 * @brief função que ajusta a posição do disparador.
 *
 * @param 'disp' será o disparador que será posicionado.
 * @param 'x' será a coordenada X alvo.
 * @param 'y' será a coordenada Y alvo.
 *
 * @pre o parâmetro 'disp' deve referenciar um disparador válido.
 * @post a posição do disparador 'disp' passa a ser (x, y).
 */
void posicionar_disparador(Disp disp, double x, double y);

/**
 * @brief função que anexa carregadores ao disparador.
 *
 * @param 'disp' será o disparador ao qual os carregadores serão anexados.
 * @param 'carregador_esq' será o carregador a ser anexado ao lado esquerdo do disparador.
 * @param 'carregador_dir' será o carregador a ser anexado ao lado direito do disparador.
 *
 * @pre o parâmetro 'disp' deve referenciar um disparador válido.
 * @pre o parâmetro 'carregador_esq' deve referenciar um carregador válido.
 * @pre o parâmetro 'carregador_dir' deve referenciar um carregador válido.
 * @post os carregadores indicados estarão associados ao disparador nos lados correspondentes.
 */
void anexar_carregadores(Disp disp, Carregador carregador_esq, Carregador carregador_dir);

/**
 * @brief função que desloca a carga/munição ativa do disparador para um dos lados.
 *
 * @param 'disp' será o disparador que será deslocado.
 * @param 'lado' será o lado para o qual a carga será deslocada.
 * @param 'n' será o número de posições para deslocar.
 *
 * @pre o parâmetro 'disp' deve referenciar um disparador válido.
 * @pre o parâmetro 'lado' deve ser 'E' ou 'e' para esquerda, 'D' ou 'd' para direita.
 * @pre o parâmetro 'n' deve ser maior que 0.
 * @post o estado interno de 'disp' é atualizado refletindo o novo posicionamento da carga.
 */
void shift_carga(Disp disp, char lado, int n);

/**
 * @brief função que dispara uma única carga usando a configuração/forma do disparador.
 *
 * @param 'disp' será o disparador que será disparado.
 * @param 'dx' será o deslocamento ou componente horizontal a aplicar ao projétil.
 * @param 'dy' será o deslocamento ou componente vertical a aplicar ao projétil.
 * @param 'arena' será a fila onde o projétil será enfileirado.
 *
 * @pre o parâmetro 'disp' deve referenciar um disparador válido.
 * @pre o parâmetro 'arena' deve referenciar uma fila válida.
 * @post um novo elemento representando o disparo é adicionado à arena; o estado de 'disp' pode ser modificado (por exemplo, decremento de munição).
 */
void disparar_forma(Disp disp, double dx, double dy, FILA arena);

/**
 * @brief função que realiza uma rajada de disparos a partir do disparador.
 *
 * @param 'disp' será o disparador que será disparado.
 * @param 'lado' será o lado de onde os projéteis são emitidos: 'E'/'e' para esquerda, 'D'/'d' para direita.
 * @param 'dx' será o incremento o componente horizontal aplicado entre projéteis.
 * @param 'dy' será o incremento o componente vertical aplicado entre projéteis.
 * @param 'ix' será o deslocamento horizontal inicial aplicado ao primeiro projétil.
 * @param 'iy' será o deslocamento vertical inicial aplicado ao primeiro projétil.
 * @param 'arena' será a fila onde os projéteis serão enfileirados.
 *
 * @pre o parâmetro 'disp' deve referenciar um disparador válido.
 * @pre o parâmetro 'arena' deve referenciar uma fila válida.
 * @return retorna o número de projéteis disparados com sucesso; valor negativo em caso de erro (por exemplo, parâmetros inválidos ou falha ao enfileirar).
 * @post os projéteis da rajada são adicionados à arena; o estado interno de 'disp' é atualizado de acordo com o número de disparos efetuados.
 */
int rajada_de_disparos(Disp disp, char lado, double dx, double dy, double ix, double iy, FILA arena);

/**
 * @brief função que retorna o identificador numérico do disparador.
 *
 * @param 'disp' será o disparador cujo id será retornado.
 * @return retorna o identificador numérico do disparador.
 *
 * @pre o parâmetro 'disp' deve referenciar um disparador válido.
 * @post o valor retornado corresponde ao id associado ao objeto disparador no momento da chamada.
 */
int disparador_get_id(Disp disp);
 
/**
 * @brief função que obtém a coordenada X do centro/origem do disparador.
 *
 * @param 'disp' será o disparador cuja coordenada X será retornada.
 * @return retorna a coordenada X do centro/origem do disparador.
 *
 * @pre o parâmetro 'disp' deve referenciar um disparador válido.
 * @post a função não modifica o estado do disparador.
 */
double disparador_get_x(Disp disp);
 
/**
 * @brief função que obtém a coordenada Y do centro/origem do disparador.
 *
 * @param 'disp' será o disparador cuja coordenada Y será retornada.
 * @return retorna a coordenada Y do centro/origem do disparador.
 *
 * @pre o parâmetro 'disp' deve referenciar um disparador válido.
 * @post a função não modifica o estado do disparador.
 */
double disparador_get_y(Disp disp);
 
/**
 * @brief função que retorna a forma geométrica atualmente associada ao disparo, se existir.
 *
 * @param 'disp' será o disparador cuja forma geométrica será retornada.
 * @return retorna um ponteiro para a FormaGeometrica usada no disparo atual, ou NULL se não houver nenhum disparo ativo.
 *
 * @note o ponteiro retornado referencia a estrutura gerida internamente pelo disparador; o chamador não deve liberar esse ponteiro.
 * @note a validade do ponteiro pode ser invalidada se o estado do disparador mudar (por exemplo, ao finalizar o disparo ou destruir o disparador).
 * @pre o parâmetro 'disp' deve referenciar um disparador válido.
 */
FormaGeometrica* disparador_get_em_disparo(Disp disp);

#endif