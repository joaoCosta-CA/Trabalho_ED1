#ifndef DISPADOR_H
#define DISPADOR_H

#include "fila.h"
#include "formas.h"
#include "carregador.h"

// Ponteiro opaco para o Disparador
typedef void* Disp;

// --- FUNÇÕES DE CICLO DE VIDA ---
/**
 * @brief Cria e inicializa um novo disparador.
 *
 * Constrói um objeto do tipo Disp com o identificador e a posição
 * inicial fornecidos. A função prepara o disparador para uso nas
 * operações do sistema (por exemplo, ativação, atualização de estado
 * ou detecção de colisões).
 *
 * @param id Identificador único do disparador.
 * @param x  Coordenada X da posição inicial do disparador.
 * @param y  Coordenada Y da posição inicial do disparador.
 * @return Disp Objeto Disp inicializado. Em caso de falha de alocação
 *         ou inicialização, o valor retornado dependerá da implementação
 *         (pode ser um valor sentinel/nulo ou exigir tratamento de erro
 *         pelo chamador); consulte a documentação da implementação.
 */
Disp criar_disparador(int id, double x, double y);

/**
 * @brief Destrói um disparador e libera os recursos associados.
 *
 * Libera toda a memória e recursos internos usados pelo disparador.
 * Após a chamada, o disparador não deve mais ser usado.
 *
 * @param disp Disparador a ser destruído.
 *
 * @pre O parâmetro disp deve referenciar um disparador válido previamente criado.
 */
void destruir_disparador(Disp disp);

// --- FUNÇÕES DE CONFIGURAÇÃO ---
/**
 * @brief Ajusta a posição do disparador.
 *
 * Atualiza a posição do objeto 'disp' para as coordenadas (x, y).
 * As unidades e o sistema de referência das coordenadas seguem a convenção usada pela aplicação.
 *
 * @param disp Identificador ou ponteiro para o disparador a ser posicionado. Deve referir-se a um disparador válido.
 * @param x Coordenada X alvo.
 * @param y Coordenada Y alvo.
 *
 * @pre 'disp' deve ser válido; comportamento é indefinido se inválido.
 * @post A posição do disparador 'disp' passa a ser (x, y).
 */
void posicionar_disparador(Disp disp, double x, double y);

/**
 * @brief Anexa carregadores ao disparador.
 *
 * Associa os carregadores fornecidos aos lados esquerdo e direito do disparador 'disp'.
 * Implementações podem substituir carregadores previamente associados ao chamar esta função.
 *
 * @param disp Identificador ou ponteiro para o disparador ao qual os carregadores serão anexados. Deve ser válido.
 * @param carregador_esq Carregador a ser anexado ao lado esquerdo do disparador. Deve referir-se a um carregador válido ou ao valor que represente "nenhum" conforme a API (por exemplo NULL).
 * @param carregador_dir Carregador a ser anexado ao lado direito do disparador. Deve referir-se a um carregador válido ou ao valor que represente "nenhum" conforme a API (por exemplo NULL).
 *
 * @pre 'disp' deve ser válido. 'carregador_esq' e 'carregador_dir' devem ser válidos ou corresponderem ao token de ausência definido pela implementação.
 * @post Os carregadores indicados estarão associados ao disparador nos lados correspondentes.
 */
void anexar_carregadores(Disp disp, Carregador carregador_esq, Carregador carregador_dir);

// --- FUNÇÕES DE AÇÃO ---
/**
 * @brief Desloca a carga/munição ativa do disparador para um dos lados.
 *
 * Move a posição da carga mantida por um objeto Disp em n posições no
 * sentido indicado por lado. Usado para reposicionar a carga antes de um
 * disparo ou para simular um mecanismo de recarga/rotação.
 *
 * @param disp Ponteiro/handle para o disparador (deve ser válido).
 * @param lado Caractere indicando o lado do deslocamento:
 *             'E' ou 'e' para esquerda, 'D' ou 'd' para direita.
 * @param n Número de posições para deslocar; valores <= 0 não efetuam alteração.
 *
 * @pre disp não deve ser NULL.
 * @post O estado interno de disp é atualizado refletindo o novo posicionamento
 *       da carga. Se n exceder limites internos, o comportamento depende da
 *       implementação (pode truncar ou envolver).
 */
void shift_carga(Disp disp, char lado, int n);

/**
 * @brief Dispara uma única carga usando a configuração/forma do disparador.
 *
 * Cria e envia para a FILA arena um projétil (ou representação de disparo)
 * conforme a configuração atual do Disp, aplicando deslocamentos ou
 * componentes de velocidade dx e dy ao projétil gerado.
 *
 * @param disp Ponteiro/handle para o disparador (deve ser válido).
 * @param dx Deslocamento ou componente horizontal a aplicar ao projétil.
 * @param dy Deslocamento ou componente vertical a aplicar ao projétil.
 * @param arena FILA onde o projétil será enfileirado (deve ser válida).
 *
 * @pre disp e arena não devem ser NULL.
 * @post Um novo elemento representando o disparo é adicionado à arena; o
 *       estado de disp pode ser modificado (por exemplo, decremento de munição).
 */
void disparar_forma(Disp disp, double dx, double dy, FILA arena);

/**
 * @brief Realiza uma rajada de disparos a partir do disparador.
 *
 * Emite uma sequência de projéteis segundo a configuração do Disp, controlando
 * direção/posição inicial e incrementos entre projéteis. Cada projétil gerado
 * é enfileirado na FILA arena.
 *
 * @param disp Ponteiro/handle para o disparador (deve ser válido).
 * @param lado Caractere indicando o lado de onde os projéteis são emitidos:
 *             'E'/'e' para esquerda, 'D'/'d' para direita.
 * @param dx Incremento o componente horizontal aplicado entre projéteis.
 * @param dy Incremento o componente vertical aplicado entre projéteis.
 * @param ix Deslocamento horizontal inicial aplicado ao primeiro projétil.
 * @param iy Deslocamento vertical inicial aplicado ao primeiro projétil.
 * @param arena FILA onde os projéteis serão enfileirados (deve ser válida).
 *
 * @return Número de projéteis disparados com sucesso; valor negativo em caso de erro
 *         (por exemplo, parâmetros inválidos ou falha ao enfileirar).
 *
 * @pre disp e arena não devem ser NULL.
 * @post Os projéteis da rajada são adicionados à arena; o estado interno de disp
 *       é atualizado de acordo com o número de disparos efetuados.
 */
int rajada_de_disparos(Disp disp, char lado, double dx, double dy, double ix, double iy, FILA arena);

// --- FUNÇÕES DE ACESSO (GETTERS) ---
/**
 * @brief Retorna o identificador numérico do disparador.
 *
 * @param disp Handle/ponteiro para o disparador cujo id se deseja obter.
 * @return inteiro representando o identificador único do disparador.
 *
 * @pre disp deve ser um handle válido previamente criado pela API do disparador.
 * @post O valor retornado corresponde ao id associado ao objeto disparador no momento da chamada.
 */
int disparador_get_id(Disp disp);
 
/**
 * @brief Obtém a coordenada X do centro/origem do disparador.
 *
 * @param disp Handle/ponteiro para o disparador.
 * @return valor em ponto flutuante representando a coordenada X no sistema de coordenadas usado pela aplicação.
 *
 * @pre disp deve ser válido.
 * @post A função não modifica o estado do disparador.
 */
double disparador_get_x(Disp disp);
 
/**
 * @brief Obtém a coordenada Y do centro/origem do disparador.
 *
 * @param disp Handle/ponteiro para o disparador.
 * @return valor em ponto flutuante representando a coordenada Y no sistema de coordenadas usado pela aplicação.
 *
 * @pre disp deve ser válido.
 * @post A função não modifica o estado do disparador.
 */
double disparador_get_y(Disp disp);
 
/**
 * @brief Retorna a forma geométrica atualmente associada ao disparo, se existir.
 *
 * @param disp Handle/ponteiro para o disparador.
 * @return ponteiro para a FormaGeometrica usada no disparo atual, ou NULL se não houver nenhum disparo ativo.
 *
 * @note O ponteiro retornado referencia a estrutura gerida internamente pelo disparador; o chamador não deve liberar esse ponteiro.
 * @note A validade do ponteiro pode ser invalidada se o estado do disparador mudar (por exemplo, ao finalizar o disparo ou destruir o disparador).
 * @pre disp deve ser válido.
 */
FormaGeometrica* disparador_get_em_disparo(Disp disp);

#endif