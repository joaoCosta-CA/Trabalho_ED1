#include "leitor_geo.h"
#include "../fila/fila.h"
#include "../pilha/pilha.h"
#include "../ler_arq/leitor.h"
#include "../circulo/circulo.h"
#include "../linha/linha.h"
#include "../retangulo/retangulo.h"
#include "../texto/texto.h"
#include "../texto/estilo_texto.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


// Estrutura para gerenciar todas as formas geométricas e coleções.
typedef struct {
    FILA fila_de_todas_as_formas; // Fila principal com todas as formas na ordem de criação.
    PILHA pilha_gerenciamento_memoria; // Pilha usada para facilitar a desalocação de memória.
    FILA fila_renderizacao_svg;  
    int max_id;
} ProcessadorDeFormas;

typedef struct {
    ShapeType tipo;
    void *dados_da_forma;
} FormaGeometricaStruct;


// Função auxiliar para registrar uma nova forma nas coleções
static void registrar_nova_forma(ProcessadorDeFormas *processador, ShapeType tipo, void *dados);

// Função para despachar a execução do comando correto
static void despachar_comando(const char *comando, ProcessadorDeFormas *processador);

static void desenhar_forma_svg(FILE*arquivo_svg, FormaGeometricaStruct* forma);

static void tratar_comando_circulo(ProcessadorDeFormas *processador);
static void tratar_comando_retangulo(ProcessadorDeFormas *processador);
static void tratar_comando_linha(ProcessadorDeFormas *processador);
static void tratar_comando_texto(ProcessadorDeFormas *processador);
static void tratar_comando_estilo_texto(ProcessadorDeFormas *processador);


Chao processar_arquivo_geo(DadosArquivo dados_arquivo, const char *caminho_saida, const char *sufixo_comando) {
    ProcessadorDeFormas *processador = malloc(sizeof(ProcessadorDeFormas));
    if (!processador) {
        perror("Erro: Falha ao alocar memória para o ProcessadorDeFormas");
        exit(EXIT_FAILURE);
    }
    processador->max_id = INT_MIN;

    processador->fila_de_todas_as_formas = criarFila();
    processador->pilha_gerenciamento_memoria = criarPilha();
    processador->fila_renderizacao_svg = criarFila();

    FILA linhas_de_comando = obter_fila_linhas(dados_arquivo);

    while (!fila_vazia(linhas_de_comando)) {
        char *linha = (char *)removeFila(linhas_de_comando);
        char *comando = strtok(linha, " \t\r\n");
        if (comando && comando[0] != '\0') {
            despachar_comando(comando, processador);
        }
    }

    const char *nome_base = obter_nome_arquivo(dados_arquivo);
    char nome_arquivo_sem_ext[256];
    strncpy(nome_arquivo_sem_ext, nome_base, sizeof(nome_arquivo_sem_ext) - 1);
    char *ponto = strrchr(nome_arquivo_sem_ext, '.');
    if (ponto) *ponto = '\0';

    char caminho_final_arquivo[512];
    if (sufixo_comando) {
        snprintf(caminho_final_arquivo, sizeof(caminho_final_arquivo), "%s/%s-%s.svg",
                 caminho_saida, nome_arquivo_sem_ext, sufixo_comando);
    } else {
        snprintf(caminho_final_arquivo, sizeof(caminho_final_arquivo), "%s/%s.svg",
                 caminho_saida, nome_arquivo_sem_ext);
    }

    FILE* svg = svg_iniciar(caminho_final_arquivo);
    if (svg) {
        svg_desenhar_chao(svg, (Chao)processador);
        svg_finalizar(svg);
    }
    
    return (Chao)processador;
}

// Em leitor_geo.c
// Em destruir_formas_geo (leitor_geo.c)
void destruir_formas_geo(Chao chao) {
    ProcessadorDeFormas *processador = (ProcessadorDeFormas *)chao;
    if (!processador) return;

    destruirFila(processador->fila_de_todas_as_formas);
    destruirFila(processador->fila_renderizacao_svg);

    while (!pilha_vazia(processador->pilha_gerenciamento_memoria)) {
        FormaGeometrica forma_ptr = pop(processador->pilha_gerenciamento_memoria); 
        if (forma_ptr) {
            FormaGeometricaStruct *forma = (FormaGeometricaStruct*) forma_ptr; 
            void* dados = forma->dados_da_forma; // Ponteiro para retangulo, circulo, etc.

            if (dados != NULL) { 
                switch (forma->tipo) {
                    case CIRCULO: DestruirCirc(dados); break; 
                    case RETANGULO: destruirRec(dados); break;
                    case LINHA: destruirLinha(dados); break;
                    case TEXTO: destruirTexto(dados); break;
                    case ESTILO_TEXTO: estilo_texto_destruir(dados); break;
                    default: break;
                }
            }
            free(forma); 
        }
    }

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
    FormaGeometricaStruct *capsula_da_forma = malloc(sizeof(FormaGeometricaStruct));
    if (!capsula_da_forma) {
        perror("Erro: Falha ao alocar memória para a cápsula da forma");
        exit(EXIT_FAILURE);
    }
    capsula_da_forma->tipo = tipo;
    capsula_da_forma->dados_da_forma = dados;

    insertFila(processador->fila_de_todas_as_formas, (FormaGeometrica)capsula_da_forma);
    push(processador->pilha_gerenciamento_memoria, (FormaGeometrica)capsula_da_forma);
    insertFila(processador->fila_renderizacao_svg, (FormaGeometrica)capsula_da_forma);
}

static void tratar_comando_circulo(ProcessadorDeFormas *processador) {
    char *token;
    int id;
    double x, y, r;
    char *cor_borda = NULL;
    char *cor_preenchimento = NULL;

    // ID
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) {
        fprintf(stderr, "Erro de formato: Faltando ID para o comando 'c'.\n");
        return;
    }
    id = atoi(token);

    // Atualiza max_id
    if (id > processador->max_id) {
        processador->max_id = id;
    }

    // X
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) {
        fprintf(stderr, "Erro de formato: Faltando coordenada X para o círculo ID %d.\n", id);
        return;
    }
    x = atof(token);

    // Y
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) {
        fprintf(stderr, "Erro de formato: Faltando coordenada Y para o círculo ID %d.\n", id);
        return;
    }
    y = atof(token);

    // Raio (r)
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) {
        fprintf(stderr, "Erro de formato: Faltando raio (r) para o círculo ID %d.\n", id);
        return;
    }
    r = atof(token);

    // Cor da Borda
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) {
        fprintf(stderr, "Erro de formato: Faltando cor da borda para o círculo ID %d.\n", id);
        return;
    }
    cor_borda = token;

    // Cor de Preenchimento
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) {
        fprintf(stderr, "Erro de formato: Faltando cor de preenchimento para o círculo ID %d.\n", id);
        return;
    }
    cor_preenchimento = token;

    // Cria o círculo apenas se todos os parâmetros foram lidos com sucesso
    Circulo c = CriarCirc(id, x, y, r, cor_borda, cor_preenchimento);
    if (c) {
        registrar_nova_forma(processador, CIRCULO, c);
    } else {
        fprintf(stderr, "Erro ao criar objeto Circulo ID %d.\n", id);
    }
}

static void tratar_comando_retangulo(ProcessadorDeFormas *processador) {
    char *token;
    int id;
    double x, y, w, h;
    char *cor_borda = NULL;
    char *cor_preenchimento = NULL;

    // ID
    token = strtok(NULL, " \t\r\n"); 
    if (token == NULL) { 
        fprintf(stderr, "Erro de formato: Faltando ID para o comando 'r'.\n"); 
        return;
    }
    id = atoi(token);

    // Atualiza max_id (após ler o ID com sucesso)
    if (id > processador->max_id) {
        processador->max_id = id;
    }

    // X
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { 
        fprintf(stderr, "Erro de formato: Faltando coordenada X para o retângulo ID %d.\n", id); 
        return; 
    }
    x = atof(token);

    // Y
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { 
        fprintf(stderr, "Erro de formato: Faltando coordenada Y para o retângulo ID %d.\n", id); 
        return; 
    }
    y = atof(token);

    // Largura (w)
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { 
        fprintf(stderr, "Erro de formato: Faltando largura (w) para o retângulo ID %d.\n", id); 
        return; 
    }
    w = atof(token);

    // Altura (h)
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { 
        fprintf(stderr, "Erro de formato: Faltando altura (h) para o retângulo ID %d.\n", id); 
        return; 
    }
    h = atof(token);

    // Cor da Borda
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { 
        fprintf(stderr, "Erro de formato: Faltando cor da borda para o retângulo ID %d.\n", id); 
        return; 
    }
    cor_borda = token;

    // Cor de Preenchimento
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { 
        fprintf(stderr, "Erro de formato: Faltando cor de preenchimento para o retângulo ID %d.\n", id); 
        return; 
    }
    cor_preenchimento = token;

    // Cria o retângulo apenas se todos os parâmetros foram lidos
    Retangulo r = criarRec(id, x, y, w, h, cor_borda, cor_preenchimento);
    if (r) {
        registrar_nova_forma(processador, RETANGULO, r);
    } else {
        fprintf(stderr, "Erro ao criar objeto Retangulo ID %d.\n", id);
    }
}

static void tratar_comando_linha(ProcessadorDeFormas *processador) {
    char *token;
    int id;
    double x1, y1, x2, y2;
    char *cor = NULL;

    // ID
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { fprintf(stderr, "Erro ao ler ID da linha.\n"); return; }
    id = atoi(token);
     if(id > processador->max_id){
        processador->max_id = id;
    }

    // X1
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { fprintf(stderr, "Erro ao ler x1 da linha ID %d.\n", id); return; }
    x1 = atof(token);

    // Y1
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { fprintf(stderr, "Erro ao ler y1 da linha ID %d.\n", id); return; }
    y1 = atof(token);

    // X2
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { fprintf(stderr, "Erro ao ler x2 da linha ID %d.\n", id); return; }
    x2 = atof(token);

    // Y2
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { fprintf(stderr, "Erro ao ler y2 da linha ID %d.\n", id); return; }
    y2 = atof(token);

    // Cor
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { fprintf(stderr, "Erro ao ler cor da linha ID %d.\n", id); return; }
    cor = token; 

    // Cria a linha apenas se todos os parâmetros foram lidos com sucesso
    Linha l = criarLinha(id, x1, y1, x2, y2, cor);
    if (l) {
        registrar_nova_forma(processador, LINHA, l);
    } else {
         fprintf(stderr, "Erro ao criar objeto Linha ID %d.\n", id);
    }
}

static void tratar_comando_texto(ProcessadorDeFormas *processador) {
    char *token;
    int id;
    double x, y;
    char *cor_borda = NULL;
    char *cor_preenchimento = NULL;
    char *ancora_str = NULL;
    char ancora_char = 'i';
    char *conteudo_texto = NULL;

    // ID
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { 
        fprintf(stderr, "Erro de formato: Faltando ID para o comando 't'.\n"); 
        return; 
    }
    id = atoi(token);

    // Atualiza max_id
    if (id > processador->max_id) {
        processador->max_id = id;
    }

    // X
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { 
        fprintf(stderr, "Erro de formato: Faltando coordenada X para o texto ID %d.\n", id); 
        return; 
    }
    x = atof(token);

    // Y
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { 
        fprintf(stderr, "Erro de formato: Faltando coordenada Y para o texto ID %d.\n", id); 
        return; 
    }
    y = atof(token);

    // Cor da Borda
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { 
        fprintf(stderr, "Erro de formato: Faltando cor da borda para o texto ID %d.\n", id); 
        return; 
    }
    cor_borda = token;

    // Cor de Preenchimento
    token = strtok(NULL, " \t\r\n");
    if (token == NULL) { 
        fprintf(stderr, "Erro de formato: Faltando cor de preenchimento para o texto ID %d.\n", id); 
        return; 
    }
    cor_preenchimento = token;

    // Âncora
    token = strtok(NULL, " \t\r\n");
    if (token == NULL || strlen(token) != 1) {
        fprintf(stderr, "Erro de formato: Faltando ou inválida âncora (i, m, f) para o texto ID %d.\n", id); 
        return; 
    }
    ancora_str = token;
    ancora_char = ancora_str[0];
    if (ancora_char != 'i' && ancora_char != 'm' && ancora_char != 'f') {
        fprintf(stderr, "Erro de formato: Âncora inválida ('%c') para o texto ID %d. Use 'i', 'm' ou 'f'.\n", ancora_char, id);
        return;
    }

    char* inicio_conteudo = token + 1;
    if (*inicio_conteudo == ' ' || *inicio_conteudo == '\t') {
         inicio_conteudo++;

         int len = strlen(inicio_conteudo);
         while (len > 0 && (inicio_conteudo[len-1] == ' ' || inicio_conteudo[len-1] == '\t' || inicio_conteudo[len-1] == '\r' || inicio_conteudo[len-1] == '\n')) {
             inicio_conteudo[--len] = '\0';
         }
         conteudo_texto = inicio_conteudo;
    } else if (*inicio_conteudo == '\0' || *inicio_conteudo == '\n' || *inicio_conteudo == '\r') { 
         fprintf(stderr, "Erro de formato: Faltando conteúdo do texto para o texto ID %d.\n", id); 
         return;
    } else {
         fprintf(stderr, "Erro de formato: Esperado espaço após a âncora para o texto ID %d.\n", id); 
         return;
    }
    
    // Verifica se, após a limpeza, o conteúdo não ficou vazio
    if (conteudo_texto == NULL || *conteudo_texto == '\0') {
         fprintf(stderr, "Erro de formato: Conteúdo do texto vazio para o texto ID %d.\n", id); 
         return;
    }


    // Cria o texto apenas se todos os parâmetros foram lidos
    Texto t = criar_texto(id, x, y, cor_borda, cor_preenchimento, ancora_char, conteudo_texto);
    if (t) {
        registrar_nova_forma(processador, TEXTO, t);
    } else {
        fprintf(stderr, "Erro ao criar objeto Texto ID %d.\n", id);
    }
}

static void tratar_comando_estilo_texto(ProcessadorDeFormas *processador) {
    char *familia = strtok(NULL, " ");
    char *peso_str = strtok(NULL, " ");
    int tamanho = atoi(strtok(NULL, " "));
    EstiloTexto ts = estilo_texto_criar(familia, peso_str[0], tamanho);
    registrar_nova_forma(processador, ESTILO_TEXTO, ts);
}

static void desenhar_forma_svg(FILE* arquivo_svg, FormaGeometricaStruct* forma) {
    if (!arquivo_svg || !forma) return;

    switch (forma->tipo) {
        case CIRCULO: {
            Circulo c = (Circulo)forma->dados_da_forma;
            fprintf(arquivo_svg, "\t<circle cx='%.2f' cy='%.2f' r='%.2f' fill='%s' stroke='%s'/>\n",
                    circulo_get_x(c), circulo_get_y(c), circulo_get_raio(c),
                    circulo_get_corp(c), circulo_get_corb(c));
            break;
        }
        case RETANGULO: {
            Retangulo r = (Retangulo)forma->dados_da_forma;
            fprintf(arquivo_svg, "\t<rect x='%.2f' y='%.2f' width='%.2f' height='%.2f' fill='%s' stroke='%s'/>\n",
                    retangulo_get_x(r), retangulo_get_y(r), retangulo_get_larg(r),
                    retangulo_get_altura(r), retangulo_get_corp(r), retangulo_get_corb(r));
            break;
        }
        case LINHA: {
            Linha l = (Linha)forma->dados_da_forma;
            fprintf(arquivo_svg, "\t<line x1='%.2f' y1='%.2f' x2='%.2f' y2='%.2f' stroke='%s'/>\n",
                    linha_get_x1(l), linha_get_y1(l), linha_get_x2(l),
                    linha_get_y2(l), linha_get_cor(l));
            break;
        }
        case TEXTO: {
            Texto t = (Texto)forma->dados_da_forma;
            char caractere_ancora = texto_get_ancora(t);
            const char *ancora_svg = "start";
            if (caractere_ancora == 'm') ancora_svg = "middle";
            else if (caractere_ancora == 'f') ancora_svg = "end";
            fprintf(arquivo_svg, "\t<text x='%.2f' y='%.2f' fill='%s' stroke='%s' text-anchor='%s'>%s</text>\n",
                    texto_get_x(t), texto_get_y(t), texto_get_corp(t),
                    texto_get_corb(t), ancora_svg, texto_get_conteudo(t));
            break;
        }
        default:
            break;
    }
}

FILE* svg_iniciar(const char* caminho_completo) {
    FILE* arquivo_svg = fopen(caminho_completo, "w");
    if (arquivo_svg) {
        fprintf(arquivo_svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1000 1000\">\n");
    } else {
        perror("Erro ao iniciar arquivo SVG");
        exit(EXIT_FAILURE);
    }
    return arquivo_svg;
}

void svg_desenhar_chao(FILE* arquivo_svg, Chao chao) {
    if (!arquivo_svg || !chao) return;
    
    ProcessadorDeFormas* processador = (ProcessadorDeFormas*)chao;

    IteradorFila it = fila_obter_iterador(processador->fila_renderizacao_svg);
    while (iterador_tem_proximo(it)) {
        FormaGeometricaStruct *forma = (FormaGeometricaStruct *)iterador_obter_proximo(it);
        desenhar_forma_svg(arquivo_svg, forma);
    }
}

void svg_finalizar(FILE* arquivo_svg) {
    if (arquivo_svg) {
        fprintf(arquivo_svg, "</svg>\n");
        fclose(arquivo_svg);
    }
}

FILA leitor_geo_get_fila_principal(Chao chao) {
    ProcessadorDeFormas *proc = (ProcessadorDeFormas *)chao;
    return proc->fila_de_todas_as_formas;
}

ShapeType forma_get_tipo(FormaGeometrica forma) {
    if (forma == NULL) {
       return -1;
    }
    FormaGeometricaStruct* f = (FormaGeometricaStruct*)forma;
    return f->tipo;
}

void* forma_get_dados(FormaGeometrica forma) {
    FormaGeometricaStruct* f = (FormaGeometricaStruct*)forma;
    return f->dados_da_forma;
}

int leitor_geo_get_max_id(Chao chao) {
    ProcessadorDeFormas *proc = (ProcessadorDeFormas *)chao;
    if (!proc) return 0;
    return (proc->max_id > 0) ? proc->max_id : 0;
}

double forma_get_x(FormaGeometrica forma) {
    if (!forma) return 0.0;
    void* dados = forma_get_dados(forma);
    switch (forma_get_tipo(forma)) {
        case CIRCULO: return circulo_get_x(dados);
        case RETANGULO: return retangulo_get_x(dados);
        case LINHA: return linha_get_x1(dados);
        case TEXTO: return texto_get_x(dados);
        default: return 0.0;
    }
}

double forma_get_y(FormaGeometrica forma) {
    if (!forma) return 0.0;
    void* dados = forma_get_dados(forma);
    switch (forma_get_tipo(forma)) {
        case CIRCULO: return circulo_get_y(dados);
        case RETANGULO: return retangulo_get_y(dados);
        case LINHA: return linha_get_y1(dados);
        case TEXTO: return texto_get_y(dados);
        default: return 0.0;
    }
}

const char* forma_get_cor_preenchimento(FormaGeometrica forma) {
    if (!forma) return NULL;
    void* dados = forma_get_dados(forma);
    switch (forma_get_tipo(forma)) {
        case CIRCULO: return circulo_get_corp(dados);
        case RETANGULO: return retangulo_get_corp(dados);
        case TEXTO: return texto_get_corp(dados);
        case LINHA: return NULL;
        default: return NULL;
    }
}

const char* forma_get_cor_borda(FormaGeometrica forma) {
    if (!forma) return NULL;
    void* dados = forma_get_dados(forma);
    switch (forma_get_tipo(forma)) {
        case CIRCULO: return circulo_get_corb(dados);
        case RETANGULO: return retangulo_get_corb(dados);
        case TEXTO: return texto_get_corb(dados);
        case LINHA: return linha_get_cor(dados);
        default: return NULL;
    }
}

void forma_set_cor_borda(FormaGeometrica forma, const char* nova_cor) {
    if (!forma || !nova_cor) return;
    void* dados = forma_get_dados(forma);
    switch (forma_get_tipo(forma)) {
        case CIRCULO:
            circulo_set_corb(dados, nova_cor);
            break;
        case RETANGULO:
            retangulo_set_corb(dados, nova_cor);
            break;
        case TEXTO:
            texto_set_corb(dados, nova_cor);
            break;
        case LINHA:
            linha_set_cor(dados, nova_cor);
            break;
        default:
            break;
    }
}

int forma_get_id(FormaGeometrica forma) {
    if (!forma) return -1;
    void* dados = forma_get_dados(forma);
    switch (forma_get_tipo(forma)) {
        case CIRCULO: return circulo_get_id(dados);
        case RETANGULO: return retangulo_get_id(dados);
        case LINHA: return linha_get_id(dados);
        case TEXTO: return texto_get_id(dados);
        default: return -1;
    }
}

void destruir_forma_completa(FormaGeometrica forma) {
    if (!forma) return;
    void* dados = forma_get_dados(forma);
    switch (forma_get_tipo(forma)) {
        case CIRCULO: DestruirCirc(dados); break;
        case RETANGULO: destruirRec(dados); break;
        case LINHA: destruirLinha(dados); break;
        case TEXTO: destruirTexto(dados); break;
        case ESTILO_TEXTO: estilo_texto_destruir(dados); break;
    }
}


FormaGeometrica forma_clonar(FormaGeometrica forma_original, int* proximo_id) {
    if (!forma_original || !proximo_id) return NULL;

    ShapeType tipo = forma_get_tipo(forma_original);
    void* dados_originais = forma_get_dados(forma_original);
    void* dados_clonados = NULL;

    const char* cor_borda_orig = forma_get_cor_borda(forma_original);
    const char* cor_preench_orig = forma_get_cor_preenchimento(forma_original);

    const char* nova_cor_borda = cor_preench_orig ? cor_preench_orig : "black";
    const char* nova_cor_preench = cor_borda_orig ? cor_borda_orig : "none";

    int novo_id = (*proximo_id)++; 

    switch (tipo) {
        case CIRCULO:
            dados_clonados = CriarCirc(novo_id, circulo_get_x(dados_originais), circulo_get_y(dados_originais),
                                       circulo_get_raio(dados_originais), nova_cor_borda, nova_cor_preench);
            break;
        case RETANGULO:
            dados_clonados = criarRec(novo_id, retangulo_get_x(dados_originais), retangulo_get_y(dados_originais),
                                      retangulo_get_larg(dados_originais), retangulo_get_altura(dados_originais),
                                      nova_cor_borda, nova_cor_preench);
            break;
        case LINHA:
            dados_clonados = criarLinha(novo_id, linha_get_x1(dados_originais), linha_get_y1(dados_originais),
                                        linha_get_x2(dados_originais), linha_get_y2(dados_originais),
                                        nova_cor_preench);
            break;
        case TEXTO:
            dados_clonados = criar_texto(novo_id, texto_get_x(dados_originais), texto_get_y(dados_originais),
                                         nova_cor_borda, nova_cor_preench, texto_get_ancora(dados_originais),
                                         texto_get_conteudo(dados_originais));
            break;
        default:
             fprintf(stderr, "Erro: Tentativa de clonar tipo de forma não suportado (%d).\n", tipo);
             (*proximo_id)--;
             return NULL;
    }

    if (!dados_clonados) {
        fprintf(stderr, "Erro na alocação da forma específica durante a clonagem.\n");
        (*proximo_id)--; 
        return NULL;
    }

    FormaGeometricaStruct *capsula_clone = malloc(sizeof(FormaGeometricaStruct));
    if (!capsula_clone) {
        perror("Erro: Falha ao alocar memória para a cápsula do clone");
        switch(tipo) {
             case CIRCULO: DestruirCirc(dados_clonados); break;
             case RETANGULO: destruirRec(dados_clonados); break;
             case LINHA: destruirLinha(dados_clonados); break;
             case TEXTO: destruirTexto(dados_clonados); break;
        }
        (*proximo_id)--;
        return NULL;
    }
    capsula_clone->tipo = tipo;
    capsula_clone->dados_da_forma = dados_clonados;

    return (FormaGeometrica)capsula_clone;
}

FILA leitor_geo_get_fila_renderizacao(Chao chao) {
    ProcessadorDeFormas *proc = (ProcessadorDeFormas *)chao;
    if (!proc) {
        return NULL;
    }
    return proc->fila_renderizacao_svg;
}

void leitor_geo_limpar_fila_renderizacao(Chao chao) {
    ProcessadorDeFormas *proc = (ProcessadorDeFormas *)chao;
    if (!proc || !proc->fila_renderizacao_svg) {
        return;
    }
    while (!fila_vazia(proc->fila_renderizacao_svg)) {
        removeFila(proc->fila_renderizacao_svg);
    }
}