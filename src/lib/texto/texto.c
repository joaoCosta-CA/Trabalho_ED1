#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"

#define TAMANHO_COR 30
#define TAMANHO_CONTEUDO 256

struct TextoStruct {
    int id;
    float x;
    float y;
    char corb[TAMANHO_COR];
    char corp[TAMANHO_COR];
    char ancora;
    char conteudo[TAMANHO_CONTEUDO];
};

// A assinatura da função agora corresponde exatamente à do arquivo .h
Texto criar_texto(int id, float x, float y, const char* corb, const char* corp, char ancora, const char* conteudo) {
    // Aloca memória para a estrutura interna.
    struct TextoStruct* novo_texto = malloc(sizeof(struct TextoStruct));
    if (!novo_texto) {
        perror("Falha ao alocar memória para o texto");
        return NULL; // Retorna NULL se malloc falhar.
    }

    // Atribui os valores numéricos e o caractere.
    novo_texto->id = id;
    novo_texto->x = x;
    novo_texto->y = y;
    novo_texto->ancora = ancora;

    snprintf(novo_texto->corb, TAMANHO_COR, "%s", corb ? corb : "");
    snprintf(novo_texto->corp, TAMANHO_COR, "%s", corp ? corp : "");
    snprintf(novo_texto->conteudo, TAMANHO_CONTEUDO, "%s", conteudo ? conteudo : "");

    // Retorna o ponteiro para a estrutura como um ponteiro opaco 'Texto' (void*).
    return novo_texto;
}

float area_texto(const Texto t) {
    if (!t) {
        return 0.0f;
    }
    const struct TextoStruct* texto_interno = (const struct TextoStruct*) t;

    return 20.0f * (float)strlen(texto_interno->conteudo);
}

void liberar_texto(Texto t) {
    free(t);
}

int texto_get_id(const Texto t) {
    if (!t) return -1;
    struct TextoStruct* texto = (struct TextoStruct*)t;
    return texto->id;
}

float texto_get_x(const Texto t) {
    if (!t) return 0.0f;
    struct TextoStruct* texto = (struct TextoStruct*)t;
    return texto->x;
}

float tedxto_get_y(const Texto t) {
    if (!t) return 0.0f;
    struct TextoStruct* texto = (struct TextoStruct*)t;
    return texto->y;
}

// In texto.c
char texto_get_ancora(Texto t) {
    if (!t) return '\0'; // Return a null character for error/null input
    
    // Cast to your internal struct
    struct TextoStruct* texto = (struct TextoStruct*)t;
    
    // Return the character value directly
    return texto->ancora;
}

const char* texto_get_corb(const Texto t) {
    if (!t) return NULL;
    struct TextoStruct* texto = (struct TextoStruct*)t;
    return texto->corb;
}