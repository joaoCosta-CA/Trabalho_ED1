#ifndef CARREGADOR_H
#define CARREGADOR_H

#include "lib/leitor_geo/leitor_geo.h"
#include "lib/pilha/pilha.h"

// Ponteiro opaco para o Carregador
typedef void* Carregador;

// --- Funções do TAD Carregador ---

Carregador criar_carregador(int id);
void destruir_carregador(Carregador c);
int carregador_get_id(Carregador c);

// Funções para manipular as formas dentro do carregador
void carregador_municia_forma(Carregador c, FormaGeometrica forma);
FormaGeometrica carregador_retira_forma(Carregador c);
int carregador_esta_vazio(Carregador c);

/**
 * @brief Retorna um ponteiro para a pilha interna do carregador.
 * @param c O carregador.
 * @return Um ponteiro para a PILHA.
 */
PILHA carregador_get_pilha(Carregador c);

#endif