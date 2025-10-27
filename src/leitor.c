#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "leitor.h"



char* duplicar_string(const char* s) {
    if (!s) return NULL;
    char* d = malloc(strlen(s) + 1);
    if (!d) return NULL;
    strcpy(d, s);
    return d;
}

typedef struct {
    char* caminho_completo;
    char* nome_arquivo;
    FILA fila_de_linhas;
} LeitorInfo;



DadosArquivo dados_arquivo_criar(const char *caminho_arquivo) {
    if (!caminho_arquivo) return NULL;

    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        return NULL;
    }

    LeitorInfo* info = (LeitorInfo*)malloc(sizeof(LeitorInfo));
    if (!info) {
        fclose(arquivo);
        return NULL;
    }

    info->caminho_completo = duplicar_string(caminho_arquivo);
    info->fila_de_linhas = criarFila();

    const char *barra = strrchr(caminho_arquivo, '/');
    if (barra) {
        info->nome_arquivo = duplicar_string(barra + 1);
    } else {
        info->nome_arquivo = duplicar_string(caminho_arquivo);
    }

    char *linha = NULL;
    size_t len = 0;
    while (getline(&linha, &len, arquivo) != -1) {
        linha[strcspn(linha, "\n")] = 0;
        insertFila(info->fila_de_linhas, duplicar_string(linha));
    }

    free(linha);
    fclose(arquivo);

    return info;
}

void dados_arquivo_destruir(DadosArquivo dados) {
    if (!dados) return;

    LeitorInfo* info = (LeitorInfo*)dados;

    free(info->caminho_completo);
    free(info->nome_arquivo);

    while (!fila_vazia(info->fila_de_linhas)) {
        char* linha = (char*)removeFila(info->fila_de_linhas);
        free(linha);
    }


    destruirFila(info->fila_de_linhas);
    free(info);
}

const char *obter_nome_arquivo(DadosArquivo dados) {
    if (!dados) return NULL;

    LeitorInfo* info = (LeitorInfo*)dados;
    
    return info->nome_arquivo;
}

FILA obter_fila_linhas(DadosArquivo dados) {
    if (!dados) return NULL;

    LeitorInfo* info = (LeitorInfo*)dados;
    return info->fila_de_linhas;
}