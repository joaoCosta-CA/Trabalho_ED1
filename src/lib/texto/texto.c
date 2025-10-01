#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h" // Inclui o cabeçalho com as declarações corretas

// A capacidade dos arrays de caracteres, incluindo o espaço para o terminador nulo.
#define TAMANHO_COR 30
#define TAMANHO_CONTEUDO 256

// Esta é a definição INTERNA e SECRETA da sua estrutura.
// O nome "TextoStruct" é usado apenas DENTRO deste arquivo .c.
// O usuário da biblioteca só conhece o tipo opaco "Texto" (void*).
struct TextoStruct {
    int id;
    float x;
    float y;
    char cor[TAMANHO_COR];
    char conteudo[TAMANHO_CONTEUDO];
};

// A assinatura da função agora corresponde exatamente à do arquivo .h
Texto criar_texto(float x, float y, const char* cor, const char* conteudo, int id) {
    // Aloca memória para a estrutura interna.
    struct TextoStruct* novo_texto = malloc(sizeof(struct TextoStruct));
    if (!novo_texto) {
        return NULL; // Retorna NULL se malloc falhar.
    }

    // Atribui os valores.
    novo_texto->id = id;
    novo_texto->x = x;
    novo_texto->y = y;

    // Copia as strings de forma segura.
    snprintf(novo_texto->cor, TAMANHO_COR, "%s", cor ? cor : "");
    snprintf(novo_texto->conteudo, TAMANHO_CONTEUDO, "%s", conteudo ? conteudo : "");

    // Retorna o ponteiro para a estrutura como um ponteiro opaco 'Texto' (void*).
    // A conversão de 'struct TextoStruct*' para 'void*' é implícita e segura.
    return novo_texto;
}

// A assinatura corresponde ao .h: recebe 'const Texto' (que é 'const void*')
float area_texto(const Texto t) {
    if (!t) {
        return 0.0f;
    }
    // Para usar os dados, precisamos converter o ponteiro opaco (void*) de volta
    // para o tipo da nossa estrutura interna (struct TextoStruct*).
    const struct TextoStruct* texto_interno = (const struct TextoStruct*) t;

    // A lógica de cálculo permanece a mesma.
    return 20.0f * (float)strlen(texto_interno->conteudo);
}

// A assinatura corresponde ao .h: recebe 'Texto' (que é 'void*')
void liberar_texto(Texto t) {
    // O ponteiro 't' (que é um void*) é o mesmo ponteiro que malloc retornou.
    // A função free() aceita um void* diretamente.
    free(t);
}