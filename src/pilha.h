#ifndef PILHA_H
#define PILHA_H

typedef void *PILHA;

/**
 * @brief cria uma nova pilha
 * @return retorna um ponteiro para a pilha criado ou NULL caso a alocação de memória falhe
 */
PILHA criarPilha();

/**
 * @brief função que inser um valor na pilha
 * @param 'pilha' será a própria pilha que terá o valor inserido
 * @param 'valor' alguma forma geométrica que irá ser inserida dentro da pilha
 */
void push(PILHA pilha, void *valor);

/**
 * @brief função que remove o último elemento inserido na pilha
 * @param 'pilha' será a própria pilha que terá o valor removido e a memória liberada
 * @return retorna o valor removido ou NULL caso a pilha esteja vazia
 */
void* pop(PILHA pilha);

/**
 * @brief função que verifica se a pilha está vazia
 * @param 'pilha' será a pilha que terá a verificação feita
 * @return retorna 1 se a pilha estiver vazia e 0 caso contrário
 */
int pilha_vazia(const PILHA pilha);

/**
 * @brief função que retorna o tamanho da pilha
 * @param 'pilha' será a pilha que terá o tamanho verficado
 * @return retorna o tamanho da pilha
 */
int pilha_tamanho(const PILHA pilha);

 /**
  * @brief função para desalocar a memória alocada para a pilha
  * @param 'pilha' será a pilha que terá toda a memória liberada
  */
 void destruirPilha(PILHA pilha);   

/**
 * @brief função que retorna o número de elementos na pilha.
 * @param 'pilha_g' será o ponteiro opaco para a pilha.
 * @return retorna o número de elementos, ou -1 se a pilha for NULL.
 */
int pilha_get_tamanho(PILHA pilha_g);
#endif