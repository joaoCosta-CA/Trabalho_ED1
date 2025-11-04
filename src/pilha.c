#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct Nod {
    void* valor;
    struct Nod* prox;
} Nod;

typedef Nod* Node;

typedef struct {
    Node topo;
    int tamanho;
} Pilha;

PILHA criarPilha(){
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    if(!pilha)return NULL;

    pilha->topo = NULL;
    pilha->tamanho = 0;

    return pilha;
}

void push(PILHA pilha_g, void* valor){
    Pilha* pilha = (Pilha*)pilha_g;
    if(!pilha)return;

    Node novo = (Node)malloc(sizeof(struct Nod));
    if(!novo)return;

    novo->valor = valor;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;

}

int pilha_vazia(const PILHA pilha_g){
    Pilha* pilha = (Pilha*)pilha_g;
    if(!pilha)return 1;

    return pilha->tamanho == 0;
}

void* pop(PILHA pilha_g){
    Pilha* pilha = (Pilha*) pilha_g;
    if(!pilha || pilha_vazia(pilha))return NULL;

    Node remove = pilha->topo;
    void* dado_retorno = remove->valor;
    pilha->topo = remove->prox;
    free(remove);
    pilha->tamanho--;

    return dado_retorno;
}

int pilha_tamanho(const PILHA pilha_g){
    Pilha* pilha = (Pilha*) pilha_g;
    if(!pilha)return 0;

    return pilha->tamanho;
}

void destruirPilha(PILHA pilha_g){
    Pilha* pilha = (Pilha*)pilha_g;
    if (pilha == NULL) {
        return;
    }

    if (pilha->tamanho > 0) {
         Node atual = pilha->topo;
         while (atual != NULL) {
             Node proximo = atual->prox;
             free(atual);
             atual = proximo;
         }
    }
    free(pilha);
}

int pilha_get_tamanho(PILHA pilha_g) {
    Pilha* pilha = (Pilha*)pilha_g;
    if (!pilha) {
        return -1;
    }
    return pilha->tamanho;
}