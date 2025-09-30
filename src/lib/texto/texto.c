#include <stdlib.h>
#include <string.h>
#include "texto.h"

// Estrutura interna do texto
typedef struct {
    int id;
    float x;
    float y;
    char cor[30];
    char conteudo[256];
} Texto;

// Cria um novo texto na posição (x, y), com cor, conteúdo e id
Texto* criar_texto(float x, float y, char* cor, char* conteudo, int id) {
    Texto* t = (Texto*) malloc(sizeof(Texto));
    if (!t) return NULL;
    t->id = id;
    t->x = x;
    t->y = y;
    strncpy(t->cor, cor, sizeof(t->cor)-1);
    t->cor[sizeof(t->cor)-1] = '\0';
    strncpy(t->conteudo, conteudo, sizeof(t->conteudo)-1);
    t->conteudo[sizeof(t->conteudo)-1] = '\0';
    return t;
}

// Calcula e retorna a "área" do texto: 20.0 * número de caracteres
float area_texto(Texto* t) {
    return 20.0f * (float)strlen(t->conteudo);
}

// Libera a memória alocada para o texto
// Libera a memória alocada para o texto
void liberar_texto(Texto* t) {
    free(t);
}