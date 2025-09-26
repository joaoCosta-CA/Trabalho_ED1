#ifndef FILA_H
#define FILA_H

/*Arquivo destina para a criação de todos os cabeçalhos das funções destinadas para filas*/

typedef void* Fila;

Fila insertFila(Fila fila, int valor);
/**
 * @brief a função tem como serventia colocar um valor expecífico dentro da fila
 * @param 'fila' será um espaço de memória reservado utilizando malloc para conseguir guardar o valor inserido 
 * @param 'valor' será um inteiro que virá a ser inserido dentro da fila(arrumar)
 */

 Fila removeFila(Fila fila);
 /**
  * @brief função para remover o primeiro elemnto da fila
  * @param 'fila' será a própria fila que ter a o valor removido e a memória liberada
  */


#endif