#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct Nod {
    void* valor;
    struct Nod* prox;
} Nod;

typedef Nod* Node;

typedef struct {
    Node inicio;
    Node fim;
    int tamanho;
} Fila;


FILA criarFila(){
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    if(!fila)return NULL;

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;

    return fila;
}


void insertFila(FILA fila_g, void* valor){
    Fila* fila = (Fila*)fila_g;
    if(fila == NULL)return;

    Node novo = (Node)malloc(sizeof(struct Nod));
    if(!novo)return;

    novo->valor = valor;
    novo->prox = NULL;

    if (fila->tamanho == 0) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->tamanho++;
}

FILA removeFila(FILA fila_g){
    Fila* fila = (Fila*)fila_g;
    if(fila->inicio == NULL || fila->tamanho == 0)return NULL;

    Node no_removido = fila->inicio;
    void* dados_retorno = no_removido->valor;

    fila->inicio = fila->inicio->prox;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(no_removido);
    fila->tamanho--;

    return dados_retorno;
}


void destruirFila(FILA fila_g) {
    Fila* fila = (Fila*)fila_g;
    if (fila == NULL) return;

    while (fila->tamanho > 0) {
        removeFila(fila);
    }

    free(fila);
}

int fila_vazia(const FILA fila_g) {
    const Fila* fila = (const Fila*)fila_g;
    if (fila == NULL) return 1;
    return fila->tamanho == 0;
}

int fila_tamanho(const FILA fila_g) {
    const Fila* fila = (const Fila*)fila_g;
    if (fila == NULL) return 0;
    return fila->tamanho;
}