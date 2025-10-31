#include "complementar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --- Definições Privadas do Módulo ---

// Buffer estático para a string de retorno
static char buffer_complementar[8]; // "#RRGGBB\0"

// Estrutura para a tabela de lookup
typedef struct {
    const char* nome;
    int hex;
} CorNomeada;

// Tabela de lookup estática
static CorNomeada tabela_cores_nomeadas[] = {
    {"red", 0xFF0000},       {"green", 0x008000},     {"blue", 0x0000FF},
    {"maroon", 0x800000},    {"purple", 0x800080},    {"fuchsia", 0xFF00FF},
    {"lime", 0x00FF00},      {"limegreen", 0x32CD32}, {"yellow", 0xFFFF00},
    {"orange", 0xFFA500},    {"cyan", 0x00FFFF},      {"aqua", 0x00FFFF},
    {"navy", 0x000080},      {"indigo", 0x4B0082},    {"gold", 0xFFD700},
    {"silver", 0xC0C0C0},    {"white", 0xFFFFFF},     {"black", 0x000000},
    {"teal", 0x008080},      {"pink", 0xFFC0CB},
};
static int num_cores_nomeadas = sizeof(tabela_cores_nomeadas) / sizeof(CorNomeada);


// --- Protótipos das Funções Estáticas (Privadas) ---

static bool parse_hex_color(const char *s, int *r, int *g, int *b);
static bool nome_para_rgb_linear(const char* nome, int* r, int* g, int* b);

// --- Implementação da Função Pública ---

const char *cor_get_complementar(const char *cor) {
    int r = 0, g = 0, b = 0; // Default: preto

    if (cor != NULL) {
        // Tenta fazer parse como Hex
        if (cor[0] == '#') {
           parse_hex_color(cor, &r, &g, &b);
        } else {
            // Se falhar, tenta fazer parse como nome (usando pesquisa linear)
            nome_para_rgb_linear(cor, &r, &g, &b);
        }
    }

    // Calcula o complemento (inverso)
    int ir = 255 - r;
    int ig = 255 - g;
    int ib = 255 - b;

    // Formata a string de saída no buffer estático
    snprintf(buffer_complementar, 8, "#%02X%02X%02X", ir, ig, ib);

    return buffer_complementar;
}


// --- Implementação das Funções Estáticas (Privadas) ---

static bool parse_hex_color(const char *s, int *r, int *g, int *b) {
    if (s == NULL || s[0] != '#') return false;

    // Suporte para formato longo: #RRGGBB
    if (strlen(s) == 7 && sscanf(s, "#%02x%02x%02x", r, g, b) == 3) {
        return true;
    }
    
    // Suporte para formato curto: #RGB
    if (strlen(s) == 4 && sscanf(s, "#%1x%1x%1x", r, g, b) == 3) {
        *r = *r * 16 + *r;
        *g = *g * 16 + *g;
        *b = *b * 16 + *b;
        return true;
    }
    
    return false; // Formato inválido
}

/**
 * Tenta ler um nome de cor usando pesquisa linear no array estático.
 */
static bool nome_para_rgb_linear(const char* nome, int* r, int* g, int* b) {
    if (nome == NULL) return false;
    
    for (int i = 0; i < num_cores_nomeadas; i++) {
        if (strcmp(nome, tabela_cores_nomeadas[i].nome) == 0) {
            int hex = tabela_cores_nomeadas[i].hex;
            *r = (hex >> 16) & 0xFF;
            *g = (hex >> 8) & 0xFF;
            *b = hex & 0xFF;
            return true;
        }
    }
    return false; // Nome não encontrado
}