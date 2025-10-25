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

typedef struct {
    Node no_atual;
} IteradorFila_Est;


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

void* removeFila(FILA fila_g){ 
    Fila* fila = (Fila*)fila_g;
    // Retorna NULL se a fila estiver vazia.
    if(fila == NULL || fila->tamanho == 0) return NULL;

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
    if (fila == NULL) {
        return;
    }

    Node atual = fila->inicio;
    while (atual != NULL) {
        Node proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(fila); 
}

int fila_vazia(const FILA fila_g) {
    const Fila* fila = (const Fila*)fila_g;
    if (fila == NULL) return 1;
    return fila->tamanho == 0;
}

int filaTamanho(const FILA fila_g) {
    const Fila* fila = (const Fila*)fila_g;
    if (fila == NULL) return 0;
    return fila->tamanho;
}


// --- Implementação das Funções do Iterador ---

IteradorFila fila_obter_iterador(FILA fila_g) {
    Fila* fila = (Fila*)fila_g;
    if (fila == NULL) return NULL;

    IteradorFila_Est* iter = (IteradorFila_Est*)malloc(sizeof(IteradorFila_Est));
    if (iter == NULL) return NULL;

    // O iterador começa apontando para o primeiro nó da fila.
    iter->no_atual = fila->inicio;

    return iter;
}

int iterador_tem_proximo(IteradorFila iterador_g) {
    IteradorFila_Est* iter = (IteradorFila_Est*)iterador_g;
    return iter != NULL && iter->no_atual != NULL;
}

void* iterador_obter_proximo(IteradorFila iterador_g) {
    IteradorFila_Est* iter = (IteradorFila_Est*)iterador_g;
    if (iter == NULL || iter->no_atual == NULL) {
        return NULL;
    }

    void* valor_retorno = iter->no_atual->valor;

    iter->no_atual = iter->no_atual->prox;

    return valor_retorno;
}

void iterador_destruir(IteradorFila iterador_g) {
    //libera a memória da estrutura do iterador.
    free(iterador_g);
}