#include "estilo_texto.h"
#include <stdlib.h>
#include <string.h>

/**
 * @struct Estrutura interna para armazenar os dados do EstiloTexto.
 * Esta definição é privada ao módulo e não deve ser acessada externamente.
 */
typedef struct {
    char *familia_da_fonte;
    char peso_da_fonte;
    int tamanho_da_fonte;
} EstiloTextoInfo;

EstiloTexto estilo_texto_criar(const char *familia_fonte, char peso_fonte,
                               int tamanho_fonte) {
    if (!familia_fonte) {
        return NULL;
    }

    EstiloTextoInfo *novo_estilo = malloc(sizeof(EstiloTextoInfo));
    if (!novo_estilo) {
        return NULL;
    }

    size_t tamanho_string = strlen(familia_fonte) + 1;
    novo_estilo->familia_da_fonte = malloc(tamanho_string);

    if (!novo_estilo->familia_da_fonte) {
        free(novo_estilo);
        return NULL;
    }

    strcpy(novo_estilo->familia_da_fonte, familia_fonte);
    novo_estilo->peso_da_fonte = peso_fonte;
    novo_estilo->tamanho_da_fonte = tamanho_fonte;

    return novo_estilo;
}

void estilo_texto_destruir(EstiloTexto estilo) {
    if (!estilo) {
        return;
    }

    EstiloTextoInfo *estilo_info = (EstiloTextoInfo *)estilo;

    if (estilo_info->familia_da_fonte != NULL) {
        free(estilo_info->familia_da_fonte);
        estilo_info->familia_da_fonte = NULL;
    }
    
}

const char *estilo_texto_obter_familia(EstiloTexto estilo) {
    if (!estilo) {
        return NULL;
    }
    return ((EstiloTextoInfo *)estilo)->familia_da_fonte;
}

char estilo_texto_obter_peso(EstiloTexto estilo) {
    if (!estilo) {
        return '\0';
    }
    return ((EstiloTextoInfo *)estilo)->peso_da_fonte;
}

int estilo_texto_obter_tamanho(EstiloTexto estilo) {
    if (!estilo) {
        return 0;
    }
    return ((EstiloTextoInfo *)estilo)->tamanho_da_fonte;
}