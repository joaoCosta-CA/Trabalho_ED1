#include "leitor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

// Funções internas (privadas ao módulo)
static FILA carregar_linhas_para_fila(const char *caminho);
static char *ler_uma_linha(FILE *fp, char *dest, size_t max);
static char *clonar_string(const char *origem);

struct DadosArquivo {
    const char *caminho_completo;
    const char *apenas_nome;
    FILA linhas;
};

// Cria uma instância de DadosArquivo lendo o arquivo indicado
DadosArquivo *dados_arquivo_criar(const char *caminho_arquivo) {
    DadosArquivo *novo = malloc(sizeof(DadosArquivo));
    if (!novo) {
        fprintf(stderr, "[ERRO] Falha ao alocar memória para DadosArquivo\n");
        return NULL;
    }

    novo->caminho_completo = caminho_arquivo;
    const char *pos = strrchr(caminho_arquivo, '/');
    novo->apenas_nome = pos ? pos + 1 : caminho_arquivo;

    FILA f = carregar_linhas_para_fila(caminho_arquivo);
    if (!f) {
        fprintf(stderr, "[ERRO] Não foi possível ler as linhas do arquivo\n");
        free(novo);
        return NULL;
    }

    novo->linhas = f;
    return novo;
}

// Libera toda a memória alocada para DadosArquivo
void dados_arquivo_destruir(DadosArquivo *dados) {
    if (!dados) return;

    if (dados->linhas) {
        while (!filaVazia(dados->linhas)) {
            char *linha = (char *)dequeueFila(dados->linhas);
            free(linha);
        }
        desalocaFila(dados->linhas);
    }

    free(dados);
}

// Lê o conteúdo de um arquivo e armazena em uma fila
static FILA carregar_linhas_para_fila(const char *caminho) {
    FILA f = criaFila();
    if (!f) return NULL;

    FILE *fp = fopen(caminho, "r");
    if (!fp) {
        desalocaFila(f);
        return NULL;
    }

    char buffer[1024];
    while (ler_uma_linha(fp, buffer, sizeof(buffer))) {
        char *linha = clonar_string(buffer);
        if (!linha) {
            fprintf(stderr, "[ERRO] Não foi possível duplicar a linha\n");
            fclose(fp);
            while (!filaVazia(f)) {
                free(dequeueFila(f));
            }
            desalocaFila(f);
            return NULL;
        }
        enqueueFila(f, linha);
    }

    fclose(fp);
    return f;
}

// Lê uma linha do arquivo e remove o '\n' no final, se existir
static char *ler_uma_linha(FILE *fp, char *dest, size_t max) {
    if (!fgets(dest, max, fp)) return NULL;

    size_t len = strlen(dest);
    if (len && dest[len - 1] == '\n') {
        dest[len - 1] = '\0';
    }
    return dest;
}

// Faz uma cópia de string (equivalente a strdup)
static char *clonar_string(const char *origem) {
    if (!origem) return NULL;
    size_t n = strlen(origem) + 1;
    char *copia = malloc(n);
    if (copia) memcpy(copia, origem, n);
    return copia;
}

// Retorna o caminho completo
const char *obter_caminho_arquivo(const DadosArquivo *dados) {
    return dados ? dados->caminho_completo : NULL;
}

// Retorna apenas o nome do arquivo
const char *obter_nome_arquivo(const DadosArquivo *dados) {
    return dados ? dados->apenas_nome : NULL;
}

// Retorna a fila de linhas
FILA obter_fila_linhas(const DadosArquivo *dados) {
    return dados ? dados->linhas : NULL;
}
