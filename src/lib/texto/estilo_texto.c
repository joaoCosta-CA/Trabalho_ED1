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

// -------------------------------------------------------------------------
// Implementação das Funções da Interface Pública
// -------------------------------------------------------------------------

EstiloTexto estilo_texto_criar(const char *familia_fonte, char peso_fonte,
                               int tamanho_fonte) {
    // Validação do parâmetro essencial.
    if (!familia_fonte) {
        return NULL;
    }

    // Aloca a memória para a estrutura principal.
    EstiloTextoInfo *novo_estilo = malloc(sizeof(EstiloTextoInfo));
    if (!novo_estilo) {
        // Falha na alocação da estrutura.
        return NULL;
    }

    // Calcula o tamanho necessário e aloca memória para a string da família da fonte.
    size_t tamanho_string = strlen(familia_fonte) + 1;
    novo_estilo->familia_da_fonte = malloc(tamanho_string);

    if (!novo_estilo->familia_da_fonte) {
        // Falha na alocação da string, então libera a estrutura já alocada.
        free(novo_estilo);
        return NULL;
    }

    // Copia os dados para a nova estrutura.
    strcpy(novo_estilo->familia_da_fonte, familia_fonte);
    novo_estilo->peso_da_fonte = peso_fonte;
    novo_estilo->tamanho_da_fonte = tamanho_fonte;

    // Retorna o ponteiro genérico para o chamador.
    return novo_estilo;
}

void estilo_texto_destruir(EstiloTexto estilo) {
    // Verifica se o ponteiro é nulo antes de prosseguir.
    if (!estilo) {
        return;
    }

    // Converte o ponteiro genérico de volta para o tipo da estrutura interna.
    EstiloTextoInfo *estilo_info = (EstiloTextoInfo *)estilo;

    if (estilo_info->familia_da_fonte != NULL) {
        free(estilo_info->familia_da_fonte);
        estilo_info->familia_da_fonte = NULL; // Boa prática
    }
    
}

const char *estilo_texto_obter_familia(EstiloTexto estilo) {
    if (!estilo) {
        return NULL;
    }
    // Converte e acessa o membro da estrutura.
    return ((EstiloTextoInfo *)estilo)->familia_da_fonte;
}

char estilo_texto_obter_peso(EstiloTexto estilo) {
    if (!estilo) {
        // Retorna um valor nulo/padrão em caso de erro.
        return '\0';
    }
    return ((EstiloTextoInfo *)estilo)->peso_da_fonte;
}

int estilo_texto_obter_tamanho(EstiloTexto estilo) {
    if (!estilo) {
        // Retorna 0 como valor padrão em caso de erro.
        return 0;
    }
    return ((EstiloTextoInfo *)estilo)->tamanho_da_fonte;
}