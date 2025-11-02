#ifndef FILA_H
#define FILA_H

/**
 * @file fila.h
 * @brief Módulo de implementação de estrutura de dados Fila (Queue) genérica
 * 
 * Este módulo fornece uma implementação completa de uma fila genérica em C,
 * utilizando uma estrutura de dados abstrata que permite armazenar elementos
 * de qualquer tipo através de ponteiros void*. A fila segue o princípio FIFO
 * (First In, First Out), onde o primeiro elemento inserido é o primeiro a ser
 * removido.
 * 
 * @note Todas as funções que recebem FILA são seguras para uso com NULL
 *       (exceto destruirFila, que deve receber uma fila válida).
 */

typedef void *FILA;
typedef void *IteradorFila;

/**
 * @brief cria uma nova fila
 * @return retorna um ponteiro para a fila criado ou NULL caso a alocação de memória falhe
 */
FILA criarFila();

/**
 * @brief a função tem como serventia colocar um valor expecífico dentro da fila
 * @param 'fila' será um espaço de memória reservado utilizando malloc para conseguir guardar o valor inserido
 * @param 'valor' será um inteiro que virá a ser inserido dentro da fila(arrumar)
 */
void insertFila(FILA fila, void *valor);

/**
 * @brief função para remover o primeiro elemnto da fila
 * @param 'fila' será a própria fila que ter a o valor removido e a memória liberada
 */
FILA removeFila(FILA fila);

/**
 * @brief função que libera toda a memória alocada para a fila
 * @param 'fila' será a fila que terá toda a memória liberada
 */
void destruirFila(const FILA fila);

/**
 * @brief função que verifica se a fila está vazia
 * @param 'fila' será a fila que terá a verificação feita
 * @return retorna 1 se a fila estiver vazia e 0 caso contrário
 */
int fila_vazia(const FILA fila);

/**
 * @brief função que retorna o tamanho da fila
 * @param 'fila' será a fila que terá o tamanho verficado
 * @return retorna o tamanho da fila
 */
int filaTamanho(FILA fila);

/**
 * @brief Cria um iterador para percorrer a fila sem modificá-la.
 * @param fila A fila que será percorrida.
 * @return Um ponteiro para a estrutura do iterador.
 */
IteradorFila fila_obter_iterador(FILA fila);

/**
 * @brief Verifica se o iterador ainda possui um próximo elemento para visitar.
 * @param iterador O iterador da fila.
 * @return Retorna 1 (verdadeiro) se houver um próximo elemento, 0 (falso) caso contrário.
 */
int iterador_tem_proximo(IteradorFila iterador);

/**
 * @brief Retorna o próximo elemento da fila e avança o iterador.
 * @param iterador O iterador da fila.
 * @return Um ponteiro para o dado do próximo elemento na fila.
 */
void *iterador_obter_proximo(IteradorFila iterador);

/**
 * @brief Libera a memória alocada para o iterador.
 * @param iterador O iterador a ser destruído.
 */
void iterador_destruir(IteradorFila iterador);

#endif