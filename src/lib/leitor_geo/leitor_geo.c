#include "leitor_geo.h"
#include "../fila/fila.h"
#include "../pilha/pilha.h"
#include "../ler_arq/leitor.h"
#include "../circulo/circulo.h"
#include "../linha/linha.h"
#include "../retangulo/retangulo.h"
#include "../formas/formas.h"
#include "../texto/texto.h"
#include "../texto/estilo_texto.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Estrutura para gerenciar todas as formas geométricas e coleções.
typedef struct {
    FILA fila_de_todas_as_formas; // Fila principal com todas as formas na ordem de criação.
    PILHA pilha_gerenciamento_memoria; // Pilha usada para facilitar a desalocação de memória.
    FILA fila_renderizacao_svg;      // Fila para renderização no arquivo SVG.
} ProcessadorDeFormas;

// Estrutura genérica para encapsular qualquer tipo de forma.
typedef struct {
    ShapeType tipo;
    void *dados_da_forma;
} FormaGeometrica;


// Função auxiliar para registrar uma nova forma nas coleções
static void registrar_nova_forma(ProcessadorDeFormas *processador, ShapeType tipo, void *dados);

// Função para despachar a execução do comando correto
static void despachar_comando(const char *comando, ProcessadorDeFormas *processador);

// Função para gerar o arquivo de saída SVG
static void escrever_svg_de_saida(ProcessadorDeFormas *processador, const char *diretorio_saida, DadosArquivo dados_arquivo, const char *sufixo);

static void tratar_comando_circulo(ProcessadorDeFormas *processador);
static void tratar_comando_retangulo(ProcessadorDeFormas *processador);
static void tratar_comando_linha(ProcessadorDeFormas *processador);
static void tratar_comando_texto(ProcessadorDeFormas *processador);
static void tratar_comando_estilo_texto(ProcessadorDeFormas *processador);

// --- Implementação das funções ---

Chao processar_arquivo_geo(DadosArquivo dados_arquivo, const char *caminho_saida, const char *sufixo_comando) {
    ProcessadorDeFormas *processador = malloc(sizeof(ProcessadorDeFormas));
    if (!processador) {
        perror("Erro: Falha ao alocar memória para o ProcessadorDeFormas");
        exit(EXIT_FAILURE);
    }

    processador->fila_de_todas_as_formas = criarFila();
    processador->pilha_gerenciamento_memoria = criarPilha();
    processador->fila_renderizacao_svg = criarFila();

    FILA linhas_de_comando = obter_fila_linhas(dados_arquivo);

    while (!fila_vazia(linhas_de_comando)) {
        char *linha = (char *)removeFila(linhas_de_comando);
        // Tratamento de múltiplos tipos de espaçamento
        char *comando = strtok(linha, " \t\r\n");

        if (comando && comando[0] != '\0') {
            despachar_comando(comando, processador);
        }
    }

    escrever_svg_de_saida(processador, caminho_saida, dados_arquivo, sufixo_comando);
    return processador;
}

void destruir_formas_geo(Chao chao) {
    ProcessadorDeFormas *processador = (ProcessadorDeFormas *)chao;
    if (!processador) return;

    // Libera a memória de cada forma usando a pilha de gerenciamento
    while (!pilha_vazia(processador->pilha_gerenciamento_memoria)) {
        FormaGeometrica *forma = pop(processador->pilha_gerenciamento_memoria);
        if (forma) {
            switch (forma->tipo) {
            case CIRCULO: DestruirCirc(forma->dados_da_forma); break;
            case RETANGULO: destruirRec(forma->dados_da_forma); break;
            case LINHA: destruirLinha(forma->dados_da_forma); break;
            case TEXTO: destruirTexto(forma->dados_da_forma); break;
            case ESTILO_TEXTO: estilo_texto_destruir(forma->dados_da_forma); break;
            default: break;
            }
            free(forma);
        }
    }

    // Destroi as estruturas de dados
    destruirFila(processador->fila_de_todas_as_formas);
    destruirFila(processador->fila_renderizacao_svg);
    destruirPilha(processador->pilha_gerenciamento_memoria);
    free(processador);
}

// --- Implementação das funções estáticas (privadas) ---

static void despachar_comando(const char *comando, ProcessadorDeFormas *processador) {
    if (strcmp(comando, "c") == 0) {
        tratar_comando_circulo(processador);
    } else if (strcmp(comando, "r") == 0) {
        tratar_comando_retangulo(processador);
    } else if (strcmp(comando, "l") == 0) {
        tratar_comando_linha(processador);
    } else if (strcmp(comando, "t") == 0) {
        tratar_comando_texto(processador);
    } else if (strcmp(comando, "ts") == 0) {
        tratar_comando_estilo_texto(processador);
    } else {
        fprintf(stderr, "Aviso: Comando desconhecido '%s' ignorado.\n", comando);
    }
}

static void registrar_nova_forma(ProcessadorDeFormas *processador, ShapeType tipo, void *dados) {
    FormaGeometrica *capsula_da_forma = malloc(sizeof(FormaGeometrica));
    if (!capsula_da_forma) {
        perror("Erro: Falha ao alocar memória para a cápsula da forma");
        exit(EXIT_FAILURE);
    }
    capsula_da_forma->tipo = tipo;
    capsula_da_forma->dados_da_forma = dados;

    // A lógica original de adicionar a mesma forma em 3 lugares é mantida
    insertFila(processador->fila_de_todas_as_formas, capsula_da_forma);
    push(processador->pilha_gerenciamento_memoria, capsula_da_forma);
    insertFila(processador->fila_renderizacao_svg, capsula_da_forma);
}

static void tratar_comando_circulo(ProcessadorDeFormas *processador) {
    int id = atoi(strtok(NULL, " "));
    double x = atof(strtok(NULL, " "));
    double y = atof(strtok(NULL, " "));
    double r = atof(strtok(NULL, " "));
    char *cor_borda = strtok(NULL, " ");
    char *cor_preenchimento = strtok(NULL, " ");
    Circulo c = CriarCirc(id, x, y, r, cor_borda, cor_preenchimento);
    registrar_nova_forma(processador, CIRCULO, c);
}

static void tratar_comando_retangulo(ProcessadorDeFormas *processador) {
    int id = atoi(strtok(NULL, " "));
    double x = atof(strtok(NULL, " "));
    double y = atof(strtok(NULL, " "));
    double w = atof(strtok(NULL, " "));
    double h = atof(strtok(NULL, " "));
    char *cor_borda = strtok(NULL, " ");
    char *cor_preenchimento = strtok(NULL, " ");
    Retangulo r = criarRec(id, x, y, w, h, cor_borda, cor_preenchimento);
    registrar_nova_forma(processador, RETANGULO, r);
}

static void tratar_comando_linha(ProcessadorDeFormas *processador) {
    int id = atoi(strtok(NULL, " "));
    double x1 = atof(strtok(NULL, " "));
    double y1 = atof(strtok(NULL, " "));
    double x2 = atof(strtok(NULL, " "));
    double y2 = atof(strtok(NULL, " "));
    char *cor = strtok(NULL, " ");
    Linha l = criarLinha(id, x1, y1, x2, y2, cor);
    registrar_nova_forma(processador, LINHA, l);
}

static void tratar_comando_texto(ProcessadorDeFormas *processador) {
    int id = atoi(strtok(NULL, " "));
    double x = atof(strtok(NULL, " "));
    double y = atof(strtok(NULL, " "));
    char *cor_borda = strtok(NULL, " ");
    char *cor_preenchimento = strtok(NULL, " ");
    char *ancora_str = strtok(NULL, " ");
    char *conteudo_texto = strtok(NULL, "");
    Texto t = criar_texto(id, x, y, cor_borda, cor_preenchimento, ancora_str[0], conteudo_texto);
    registrar_nova_forma(processador, TEXTO, t);
}

static void tratar_comando_estilo_texto(ProcessadorDeFormas *processador) {
    char *familia = strtok(NULL, " ");
    char *peso_str = strtok(NULL, " ");
    int tamanho = atoi(strtok(NULL, " "));
    EstiloTexto ts = estilo_texto_criar(familia, peso_str[0], tamanho);
    registrar_nova_forma(processador, ESTILO_TEXTO, ts);
}

static void escrever_svg_de_saida(ProcessadorDeFormas *processador, const char *diretorio_saida,DadosArquivo dados_arquivo, const char *sufixo) {
    const char *nome_base = obter_nome_arquivo(dados_arquivo);
    char nome_arquivo_sem_ext[256];
    strncpy(nome_arquivo_sem_ext, nome_base, sizeof(nome_arquivo_sem_ext) - 1);
    char *ponto = strrchr(nome_arquivo_sem_ext, '.');
    if (ponto) *ponto = '\0';

    char caminho_final_arquivo[512];
    if (sufixo) {
        snprintf(caminho_final_arquivo, sizeof(caminho_final_arquivo), "%s/%s-%s.svg",
                 diretorio_saida, nome_arquivo_sem_ext, sufixo);
    } else {
        snprintf(caminho_final_arquivo, sizeof(caminho_final_arquivo), "%s/%s.svg",
                 diretorio_saida, nome_arquivo_sem_ext);
    }

    FILE *arquivo_svg = fopen(caminho_final_arquivo, "w");
    if (!arquivo_svg) {
        perror("Erro ao abrir o arquivo SVG de saída");
        return;
    }

    fprintf(arquivo_svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1000 1000\">\n");

    // Itera na fila de renderização para desenhar cada forma
    IteradorFila it = fila_obter_iterador(processador->fila_renderizacao_svg);
    while (iterador_tem_proximo(it)) {
        FormaGeometrica *forma = (FormaGeometrica *)iterador_obter_proximo(it);
        if (!forma) continue;

        switch (forma->tipo) {
        case CIRCULO: {
            Circulo c = (Circulo)forma->dados_da_forma;
            fprintf(arquivo_svg, "\t<circle cx='%.2fl' cy='%.2fl' r='%.2f' fill='%s' stroke='%s'/>\n",
                    circulo_get_x(c), circulo_get_y(c), circulo_get_raio(c),
                    circulo_get_corp(c), circulo_get_corb(c));
            break;
        }
        case RETANGULO: {
            Retangulo r = (Retangulo)forma->dados_da_forma;
            fprintf(arquivo_svg, "\t<rect x='%.2fl' y='%.2fl' width='%.2f' height='%.2f' fill='%s' stroke='%s'/>\n",
                    retangulo_get_x(r), retangulo_get_y(r), retangulo_get_larg(r),
                    retangulo_get_altura(r), retangulo_get_corp(r), retangulo_get_corb(r));
            break;
        }
        case LINHA: {
            Linha l = (Linha)forma->dados_da_forma;
            fprintf(arquivo_svg, "\t<line x1='%.2fl' y1='%.2fl' x2='%.2fl' y2='%.2fl' stroke='%s'/>\n",
                    linha_get_x1(l), linha_get_y1(l), linha_get_x2(l),
                    linha_get_y2(l), linha_get_cor(l));
            break;
        }
        case TEXTO: {
            Texto t = (Texto)forma->dados_da_forma;
            char caractere_ancora = texto_get_ancora(t);
            const char *ancora_svg = "start"; // Padrão 'i' (início)
            if (caractere_ancora == 'm') {
                ancora_svg = "middle";
            } else if (caractere_ancora == 'f') { // BUG CORRIGIDO: de 'e' para 'f'
                ancora_svg = "end";
            }
            fprintf(arquivo_svg, "\t<text x='%.2f' y='%.2f' fill='%s' stroke='%s' text-anchor='%s'>%s</text>\n",
                    texto_get_x(t), texto_get_y(t), texto_get_corp(t),
                    texto_get_corb(t), ancora_svg, texto_get_conteudo(t));
            break;
        }
        default:
            // O comando 'ts' não gera uma saída SVG visível, então é ignorado aqui.
            break;
        }
    }

    fprintf(arquivo_svg, "</svg>\n");
    fclose(arquivo_svg);
}