#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitor.h"



char* duplicar_string(const char* s) {
    if (!s) return NULL;
    char* d = malloc(strlen(s) + 1);
    if (!d) return NULL;
    strcpy(d, s);
    return d;
}

// --- Estrutura Interna (o "segredo" do TAD) ---
typedef struct {
    char* caminho_completo;
    char* nome_arquivo;
    FILA fila_de_linhas;
} LeitorInfo;


// --- Implementação das Funções ---

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

    // Extrai o nome do arquivo a partir do caminho
    const char *barra = strrchr(caminho_arquivo, '/');
    if (barra) {
        info->nome_arquivo = duplicar_string(barra + 1);
    } else {
        info->nome_arquivo = duplicar_string(caminho_arquivo);
    }

    // Lê as linhas do arquivo e as armazena na fila
    char *linha = NULL;
    size_t len = 0;
    while (getline(&linha, &len, arquivo) != -1) {
        // Remove o '\n' do final da linha, se houver
        linha[strcspn(linha, "\n")] = 0;
        // Insere uma cópia da linha na fila
        insertFila(info->fila_de_linhas, duplicar_string(linha));
    }

    free(linha); // getline aloca memória que precisa ser liberada
    fclose(arquivo);

    return info; // Retorna o ponteiro para a struct interna, como void*
}

void dados_arquivo_destruir(DadosArquivo dados) {
    if (!dados) return;

    // Cast para o tipo interno para poder acessar os membros
    LeitorInfo* info = (LeitorInfo*)dados;

    free(info->caminho_completo);
    free(info->nome_arquivo);

    // Libera a memória de cada linha armazenada na fila
    while (!fila_vazia(info->fila_de_linhas)) {
        char* linha = (char*)removeFila(info->fila_de_linhas);
        free(linha);
    }

    // Libera a memória da própria fila e da estrutura principal
    destruirFila(info->fila_de_linhas);
    free(info);
}

const char *obter_nome_arquivo(DadosArquivo dados) {
    if (!dados) return NULL;

    // A MÁGICA ACONTECE AQUI:
    // Cast do ponteiro genérico 'dados' para o tipo da struct interna.
    LeitorInfo* info = (LeitorInfo*)dados;
    
    // Agora você pode usar o '->' com segurança!
    return info->nome_arquivo;
}

FILA obter_fila_linhas(DadosArquivo dados) {
    if (!dados) return NULL;

    // Mesmo processo: faz o cast para acessar os membros internos.
    LeitorInfo* info = (LeitorInfo*)dados;
    return info->fila_de_linhas;
}