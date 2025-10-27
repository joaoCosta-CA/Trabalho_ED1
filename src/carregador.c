#include "carregador.h"
#include "pilha.h"

#include <stdlib.h>

typedef struct {
    int id;
    PILHA pilha_formas;
} CarregadorStruct;

Carregador criar_carregador(int id) {
    CarregadorStruct* c = malloc(sizeof(CarregadorStruct));
    if (c == NULL) {
        perror("Erro ao alocar memoria para CarregadorStruct");
        return NULL;
    }

    c->id = id;
    c->pilha_formas = criarPilha();

    if (c->pilha_formas == NULL) {
        perror("Erro ao criar a pilha interna do carregador");
        free(c);
        return NULL;
    }

    return (Carregador)c;
}

void destruir_carregador(Carregador carregador) {
    CarregadorStruct* c = (CarregadorStruct*)carregador;
    if(!c)return;
    destruirPilha(c->pilha_formas);
    free(c);
}

PILHA carregador_get_pilha(Carregador carregador) {
    if (carregador == NULL) {
        return NULL;
    }
    CarregadorStruct* c = (CarregadorStruct*)carregador;
    return c->pilha_formas;
}

int carregador_get_id(Carregador carregador) {
    if(!carregador)return -1;
    return ((CarregadorStruct*)carregador)->id;
}

void carregador_municia_forma(Carregador carregador, FormaGeometrica forma) {
    CarregadorStruct* c = (CarregadorStruct*)carregador;
    if(!c)return;
    push(c->pilha_formas, forma);
}

FormaGeometrica carregador_retira_forma(Carregador carregador) {
    if (carregador == NULL) {
        fprintf(stderr, "Erro: Tentando retirar forma de carregador NULL.\n");
        return NULL;
    }
    if (carregador_esta_vazio(carregador)) {
        return NULL;
    }
    return (FormaGeometrica)pop(((CarregadorStruct*)carregador)->pilha_formas);
}

int carregador_esta_vazio(Carregador carregador) {
    if (carregador == NULL) {
        fprintf(stderr, "Aviso: Verificando se carregador NULL está vazio (retornando true).\n");
        return 1;
    }
    CarregadorStruct* c = (CarregadorStruct*)carregador;
    PILHA pilha_interna = c->pilha_formas;

    return pilha_vazia(pilha_interna);
}