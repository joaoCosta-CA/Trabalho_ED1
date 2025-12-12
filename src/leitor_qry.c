#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "leitor_qry.h"
#include "disparador.h"
#include "carregador.h"
#include "fila.h"
#include "pilha.h"
#include "leitor_geo.h"
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "linha.h"

#define MAX_PATH_LEN 1024;


typedef struct {
    double x_inicio, y_inicio;
    double x_fim, y_fim;       
    double dx, dy;
} AnotacaoDisparo;

typedef struct {
    double x, y;
}AnotacaoEsmagamento;


// --- PROTÓTIPOS DE TODAS AS FUNÇÕES STATIC ---

// Funções de tratamento de comandos
static void tratar_comando_pd(char* params, Disp** array_disparadores, int* num_disparadores);
static void tratar_comando_lc(char* params, Chao chao, Carregador** array_carregadores, int* num_carregadores, FILE* log_txt);
static void tratar_comando_atch(char* params, Disp* array_disparadores, int num_disparadores, Carregador* array_carregadores, int num_carregadores);
static void tratar_comando_shft(char* params, Disp* array_disparadores, int num_disparadores, FILE* log_txt);
static void tratar_comando_dsp(char* params, Disp* array_disparadores, int num_disparadores, FILA arena, int* contador_disparos, AnotacaoDisparo** array_anotacoes, int* num_anotacoes, FILE* log_txt);
static void tratar_comando_rjd(char* params, Disp* array_disparadores, int num_disparadores, FILA arena, int* contador_disparos, Chao chao, double* pontuacao_total, int* total_esmagados, int* total_clonados, AnotacaoEsmagamento** array_anotacoes_esmag, int* num_anotacoes_esmag, int* proximo_id_clone, FILE* log_txt);
static void tratar_comando_calc(FILA arena, Chao chao, double* pontuacao_total,int* contador_esmagados, int* contador_clonados,AnotacaoEsmagamento** array_anotacoes_esmag, int* num_anotacoes_esmag,int* proximo_id_clone,FILE* log_txt);

// Funções auxiliares
static Disp buscar_disparador_por_id(int id, Disp* array, int tamanho);
static Carregador buscar_carregador_por_id(int id, Carregador* array, int tamanho);
static void imprimir_dados_forma(FILE* log_txt, FormaGeometrica forma);
static double forma_get_area(FormaGeometrica forma);
static bool formas_se_sobrepoem(FormaGeometrica forma1, FormaGeometrica forma2);


// Funções de sobreposição

static bool circulo_circulo_sobrepoe(FormaGeometrica c1_forma, FormaGeometrica c2_forma);
static bool retangulo_retangulo_sobrepoe(FormaGeometrica r1_forma, FormaGeometrica r2_forma);
static bool circulo_retangulo_sobrepoe(FormaGeometrica circ_forma, FormaGeometrica rect_forma);
static bool texto_get_segmento(FormaGeometrica texto_forma, double* x1, double* y1, double* x2, double* y2);
static bool linha_linha_sobrepoe(double p1x, double p1y, double q1x, double q1y, double p2x, double p2y, double q2x, double q2y);
static bool circulo_linha_sobrepoe(FormaGeometrica circ_forma, double lx1, double ly1, double lx2, double ly2);
static bool retangulo_linha_sobrepoe(FormaGeometrica rect_forma, double lx1, double ly1, double lx2, double ly2);
static double ponto_segmento_dist_quadrada(double px, double py, double ax, double ay, double bx, double by);



void processar_arquivo_qry(Chao chao, DadosArquivo dados_qry, DadosArquivo dados_geo, const char* caminho_saida) {
    Disp* array_disparadores = NULL;
    int num_disparadores = 0;
    
    Carregador* array_carregadores = NULL;
    int num_carregadores = 0;

    AnotacaoDisparo* array_anotacoes_disparo = NULL;
    int num_anotacoes_disparo = 0;

    AnotacaoEsmagamento* array_anotacoes_esmag = NULL;
    int num_anotacoes_esmag = 0;

    FILA arena_de_combate = criarFila();
    FILA arena_snapshot = NULL;  // Snapshot da arena antes do calc

    int proximo_id_clone = leitor_geo_get_max_id(chao) + 1;
    
    double pontuacao_total = 0.0;
    int instrucoes_executadas = 0;
    int total_disparos = 0;
    int total_esmagados = 0;
    int total_clonados = 0;
    
    FILE* arquivo_log_txt = NULL;

    const char* nome_base_geo = obter_nome_arquivo(dados_geo);
    char nome_geo_sem_ext[256];
    strncpy(nome_geo_sem_ext, nome_base_geo, sizeof(nome_geo_sem_ext) - 1);
    char* ponto = strrchr(nome_geo_sem_ext, '.');
    if (ponto) *ponto = '\0';

    const char* nome_base_qry = obter_nome_arquivo(dados_qry);
    char nome_qry_sem_ext[256];
    strncpy(nome_qry_sem_ext, nome_base_qry, sizeof(nome_qry_sem_ext) - 1);
    ponto = strrchr(nome_qry_sem_ext, '.');
    if (ponto) *ponto = '\0';
    
    char caminho_log_txt[1024];
    snprintf(caminho_log_txt, sizeof(caminho_log_txt), "%s/%s-%s.txt", caminho_saida, nome_geo_sem_ext, nome_qry_sem_ext);
    arquivo_log_txt = fopen(caminho_log_txt, "w");
    if (arquivo_log_txt == NULL) {
        perror("Erro ao criar arquivo de log .txt");
        fprintf(stderr, "AVISO: Nao foi possivel criar o arquivo de log. A saida TXT sera perdida.\n");
        exit(EXIT_FAILURE); 
    }

    FILA linhas_de_comando = obter_fila_linhas(dados_qry);
    while (!fila_vazia(linhas_de_comando)) {
        char* linha = (char*)removeFila(linhas_de_comando);
        
        char linha_log[512];
        strncpy(linha_log, linha, sizeof(linha_log) - 1);
        linha_log[strcspn(linha_log, "\r\n")] = 0;

        char* comando = strtok(linha, " \t");
        if (comando) {
            if(arquivo_log_txt != NULL){
                fprintf(arquivo_log_txt, "[*] %s\n", linha_log);
            }

            char* parametros = strtok(NULL, "");
            instrucoes_executadas++;

            

            if (strcmp(comando, "pd") == 0) {
                tratar_comando_pd(parametros, &array_disparadores, &num_disparadores);
            } else if (strcmp(comando, "lc") == 0) {
                tratar_comando_lc(parametros, chao, &array_carregadores, &num_carregadores, arquivo_log_txt);
            } else if (strcmp(comando, "atch") == 0) {
                tratar_comando_atch(parametros, array_disparadores, num_disparadores, array_carregadores, num_carregadores);
            } else if (strcmp(comando, "shft") == 0) {
                tratar_comando_shft(parametros, array_disparadores, num_disparadores, arquivo_log_txt);
            } else if (strcmp(comando, "dsp") == 0) {
                tratar_comando_dsp(parametros, array_disparadores, num_disparadores, arena_de_combate, &total_disparos, &array_anotacoes_disparo, &num_anotacoes_disparo, arquivo_log_txt);
            } else if (strcmp(comando, "rjd") == 0) {
                tratar_comando_rjd(parametros, array_disparadores, num_disparadores, arena_de_combate, &total_disparos, chao, &pontuacao_total, &total_esmagados, &total_clonados, &array_anotacoes_esmag, &num_anotacoes_esmag, &proximo_id_clone, arquivo_log_txt);
            } else if (strcmp(comando, "calc") == 0) {
                // Criar snapshot da arena antes do calc para visualização no SVG
                if (arena_snapshot == NULL && !fila_vazia(arena_de_combate)) {
                    arena_snapshot = criarFila();
                    IteradorFila it = fila_obter_iterador(arena_de_combate);
                    while (iterador_tem_proximo(it)) {
                        insertFila(arena_snapshot, iterador_obter_proximo(it));
                    }
                    iterador_destruir(it);
                }
                tratar_comando_calc(arena_de_combate, chao, &pontuacao_total, &total_esmagados, &total_clonados, &array_anotacoes_esmag, &num_anotacoes_esmag, &proximo_id_clone, arquivo_log_txt);
            }
        }
        free(linha);
    }


    char caminho_final_svg[1024];
    snprintf(caminho_final_svg, sizeof(caminho_final_svg), "%s/%s-%s.svg", caminho_saida, nome_geo_sem_ext, nome_qry_sem_ext);
    FILE* svg = svg_iniciar(caminho_final_svg);
    if (svg) {
        // Desenha o chão que inclui:
        // 1. Formas que não foram disparadas
        // 2. Formas que sobreviveram ao calc e voltaram
        // 3. Formas que ficaram nos carregadores
        svg_desenhar_chao(svg, chao);

    for (int i = 0; i < num_anotacoes_esmag; i++) {
        AnotacaoEsmagamento anot_esmag = array_anotacoes_esmag[i];
        fprintf(svg, "\t<text x='%.2f' y='%.2f' fill='red' font-size='15' text-anchor='middle' dominant-baseline='middle'>*</text>\n",anot_esmag.x, anot_esmag.y);
    }

        svg_finalizar(svg);
    }


    if(arquivo_log_txt) {
        fprintf(arquivo_log_txt, "\n--- ESTATÍSTICAS ---\n");
        fprintf(arquivo_log_txt, "pontuação final: %.2f\n", pontuacao_total);
        fprintf(arquivo_log_txt, "número total de instruções executadas: %d\n", instrucoes_executadas);
        fprintf(arquivo_log_txt, "número total de disparos: %d\n", total_disparos);
        fprintf(arquivo_log_txt, "número total de formas clonadas: %d\n", total_clonados);
        fprintf(arquivo_log_txt, "número total de formas esmagadas: %d\n", total_esmagados);
        fclose(arquivo_log_txt);
    }
    
    for (int i = 0; i < num_disparadores; i++) {
        destruir_disparador(array_disparadores[i]);
    }
    free(array_disparadores);

    for (int i = 0; i < num_carregadores; i++) {
        destruir_carregador(array_carregadores[i]);
    }
    free(array_carregadores);
    free(array_anotacoes_disparo);
    free(array_anotacoes_esmag);
    destruirFila(arena_de_combate);
    if (arena_snapshot != NULL) {
        destruirFila(arena_snapshot);
    }
}

static Disp buscar_disparador_por_id(int id, Disp* array, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (disparador_get_id(array[i]) == id) {
            return array[i];
        }
    }
    return NULL;
}

static Carregador buscar_carregador_por_id(int id, Carregador* array, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (carregador_get_id(array[i]) == id) {
            return array[i];
        }
    }
    return NULL;
}

static void imprimir_dados_forma(FILE* log_txt, FormaGeometrica forma) {
    if (!log_txt || !forma) return;
    
    ShapeType tipo = forma_get_tipo(forma);
    void* dados = forma_get_dados(forma);

    switch (tipo) {
        case CIRCULO:
            fprintf(log_txt, "[C] id:%d, x:%.2f, y:%.2f, r:%.2f, corb:%s, corp:%s\n",
                circulo_get_id(dados), circulo_get_x(dados), circulo_get_y(dados),
                circulo_get_raio(dados), circulo_get_corb(dados), circulo_get_corp(dados));
            break;
        case RETANGULO:
            fprintf(log_txt, "[R] id:%d, x:%.2f, y:%.2f, w:%.2f, h:%.2f, corb:%s, corp:%s\n",
                retangulo_get_id(dados), retangulo_get_x(dados), retangulo_get_y(dados),
                retangulo_get_larg(dados), retangulo_get_altura(dados),
                retangulo_get_corb(dados), retangulo_get_corp(dados));
            break;
        case LINHA:
            fprintf(log_txt, "[L] id:%d, x1:%.2f, y1:%.2f, x2:%.2f, y2:%.2f, cor:%s\n",
                linha_get_id(dados), linha_get_x1(dados), linha_get_y1(dados),
                linha_get_x2(dados), linha_get_y2(dados), linha_get_cor(dados));
            break;
        case TEXTO:
            fprintf(log_txt, "[T] id:%d, x:%.2f, y:%.2f, corb:%s, corp:%s, ancora:%c, texto:\"%s\"\n",
                texto_get_id(dados), texto_get_x(dados), texto_get_y(dados),
                texto_get_corb(dados), texto_get_corp(dados), texto_get_ancora(dados),
                texto_get_conteudo(dados));
            break;
        default:

            fprintf(log_txt, "Forma de tipo desconhecido ou sem representação textual.\n");
            break;
    }
}

static void tratar_comando_pd(char* params, Disp** array_disparadores, int* num_disparadores) {
    int id; double x, y;
    sscanf(params, "%d %lf %lf", &id, &x, &y);
    
    (*num_disparadores)++;
    *array_disparadores = realloc(*array_disparadores, (*num_disparadores) * sizeof(Disp));
    
    Disp novo_disp = criar_disparador(id, x, y);
    (*array_disparadores)[(*num_disparadores) - 1] = novo_disp;
}

static void tratar_comando_lc(char* params, Chao chao, Carregador** array_carregadores, int* num_carregadores, FILE* log_txt) {
    int id_carregador, n_formas;
    sscanf(params, "%d %d", &id_carregador, &n_formas);

    (*num_carregadores)++;
    Carregador* temp_array = realloc(*array_carregadores, (*num_carregadores) * sizeof(Carregador));
    if (temp_array == NULL) {
        perror("Erro ao realocar array de carregadores");
        (*num_carregadores)--; 
        return; 
    }
    *array_carregadores = temp_array;

    Carregador novo_carregador = criar_carregador(id_carregador);
    if (novo_carregador == NULL) {
        fprintf(stderr, "Erro ao criar carregador com ID %d\n", id_carregador);
        (*num_carregadores)--; 
        return;
    }
    (*array_carregadores)[(*num_carregadores) - 1] = novo_carregador;

    // Usar pilha temporária para inverter ordem
    // Formas do .geo: 1,2,3,4 -> pilha_temp: topo=4,fundo=1
    // Desempilhar para carregador: carregador topo=1, fundo=4
    // Ao retirar do carregador: sai 1,2,3,4 (ordem original do .geo!)
    PILHA pilha_temp = criarPilha();
    
    FILA fila_do_chao = leitor_geo_get_fila_principal(chao);
    for (int i = 0; i < n_formas && !fila_vazia(fila_do_chao); ++i) {
        FormaGeometrica forma = removeFila(fila_do_chao);
        push(pilha_temp, forma);
    }
    
    while (!pilha_vazia(pilha_temp)) {
        FormaGeometrica forma = pop(pilha_temp);
        carregador_municia_forma(novo_carregador, forma);
        if (log_txt) {
            fprintf(log_txt, "\t-> ");
            imprimir_dados_forma(log_txt, forma);
        }
    }
    
    destruirPilha(pilha_temp);
}

static void tratar_comando_atch(char* params, Disp* array_disparadores, int num_disparadores, Carregador* array_carregadores, int num_carregadores) {
    int id_disp, id_esq, id_dir;
    sscanf(params, "%d %d %d", &id_disp, &id_esq, &id_dir);

    Disp d = buscar_disparador_por_id(id_disp, array_disparadores, num_disparadores);
    if (!d) return;
    
    Carregador c_esq = buscar_carregador_por_id(id_esq, array_carregadores, num_carregadores);
    Carregador c_dir = buscar_carregador_por_id(id_dir, array_carregadores, num_carregadores);
    
    anexar_carregadores(d, c_esq, c_dir);
}

static void tratar_comando_shft(char* params, Disp* array_disparadores, int num_disparadores, FILE* log_txt) {
    int id_disp, n;
    char lado;
    sscanf(params, "%d %c %d", &id_disp, &lado, &n);

    Disp d = buscar_disparador_por_id(id_disp, array_disparadores, num_disparadores);
    if (d) {

        shift_carga(d, lado, n);
        
        FormaGeometrica forma_na_mira = disparador_get_em_disparo(d);
        if (log_txt && forma_na_mira) {
            fprintf(log_txt, "Figura em posicao de disparo: ");
            imprimir_dados_forma(log_txt, forma_na_mira);
        }
    }
}

static void tratar_comando_dsp(char* params, Disp* array_disparadores, int num_disparadores, FILA arena, int* contador_disparos, AnotacaoDisparo** array_anotacoes, int* num_anotacoes, FILE* log_txt) {
    int id_disp;
    double dx, dy;
    char visual[2] = ""; 
    sscanf(params, "%d %lf %lf %1s", &id_disp, &dx, &dy, visual);
    
    Disp d = buscar_disparador_por_id(id_disp, array_disparadores, num_disparadores);
    if (d) {
        FormaGeometrica forma_antes_disparo = disparador_get_em_disparo(d);
        
        double x_inicio = disparador_get_x(d);
        double y_inicio = disparador_get_y(d);
        
        if (forma_antes_disparo) {
            (*contador_disparos)++;
        }
        disparar_forma(d, dx, dy, arena);

        if (log_txt && forma_antes_disparo) {
            fprintf(log_txt, "Forma disparada. Dados e posicao final: ");
            imprimir_dados_forma(log_txt, forma_antes_disparo);
        }
        
        if (visual[0] == 'v' && forma_antes_disparo) {
            double x_fim = x_inicio + dx;
            double y_fim = y_inicio + dy;

            (*num_anotacoes)++;
            *array_anotacoes = realloc(*array_anotacoes, (*num_anotacoes) * sizeof(AnotacaoDisparo));

            AnotacaoDisparo* nova_anotacao = &((*array_anotacoes)[(*num_anotacoes) - 1]);
            nova_anotacao->x_inicio = x_inicio;
            nova_anotacao->y_inicio = y_inicio;
            nova_anotacao->x_fim = x_fim;
            nova_anotacao->y_fim = y_fim;
            nova_anotacao->dx = dx;
            nova_anotacao->dy = dy;
        }
    }
}

static void tratar_comando_rjd(char* params, Disp* array_disparadores, int num_disparadores, FILA arena, int* contador_disparos, Chao chao, double* pontuacao_total, int* total_esmagados, int* total_clonados __attribute__((unused)), AnotacaoEsmagamento** array_anotacoes_esmag, int* num_anotacoes_esmag, int* proximo_id_clone __attribute__((unused)), FILE* log_txt) {
    int id_disp;
    char lado;
    double dx, dy, ix, iy;
    sscanf(params, "%d %c %lf %lf %lf %lf", &id_disp, &lado, &dx, &dy, &ix, &iy);

    Disp d = buscar_disparador_por_id(id_disp, array_disparadores, num_disparadores);
    if (!d) return;

    // Acessar estrutura interna do disparador
    typedef struct {
        int id;
        double x;
        double y;
        Carregador carga_esq;
        Carregador carga_dir;
        FormaGeometrica* em_disparo;
    } DisparadorStruct;
    
    DisparadorStruct* disp_struct = (DisparadorStruct*)d;
    
    // Selecionar carregador alvo com fallback
    Carregador carga_alvo = (lado == 'd' || lado == 'D') ? disp_struct->carga_dir : disp_struct->carga_esq;
    
    // Se carregador selecionado está vazio ou NULL, tentar o outro
    if (!carga_alvo || carregador_esta_vazio(carga_alvo)) {
        Carregador outro = (lado == 'd' || lado == 'D') ? disp_struct->carga_esq : disp_struct->carga_dir;
        if (outro && !carregador_esta_vazio(outro)) {
            carga_alvo = outro;
        } else {
            return; // Ambos carregadores vazios ou NULL
        }
    }


    // Primeiro, coletar TODAS as formas do carregador em um array
    // Usar carregador_retira_forma diretamente para não acionar a lógica de devolução do shift
    const int MAX_DISPAROS = 100;
    FormaGeometrica formas_array[MAX_DISPAROS];
    int total_formas = 0;
    
    while (!carregador_esta_vazio(carga_alvo) && total_formas < MAX_DISPAROS) {
        FormaGeometrica forma = carregador_retira_forma(carga_alvo);
        if (forma) {
            formas_array[total_formas++] = forma;
        }
    }
    
    // Os carregadores já estão invertidos pelo atch, então as formas vêm na ordem correta
    // (menores primeiro)
    
    // Processar em ordem normal (menores primeiro)
    double dx_atual = dx;
    double dy_atual = dy;
    int disparos_efetuados = 0;
    FILA fila_chao = leitor_geo_get_fila_principal(chao);
    
    for (int idx = 0; idx < total_formas; idx += 2) {
        if (idx + 1 >= total_formas) {
            // Última forma ímpar
            disp_struct->em_disparo = formas_array[idx];
            disparar_forma(d, dx_atual, dy_atual, arena);
            (*contador_disparos)++;
            FormaGeometrica ultima = removeFila(arena);
            insertFila(fila_chao, ultima);
            break;
        }
        
        // Disparar PAR (I e J)
        disp_struct->em_disparo = formas_array[idx];  // I (menor do par)
        disparar_forma(d, dx_atual, dy_atual, arena);
        (*contador_disparos)++;
        dx_atual += ix;
        dy_atual += iy;
        
        disp_struct->em_disparo = formas_array[idx+1];  // J (maior do par)
        disparar_forma(d, dx_atual, dy_atual, arena);
        (*contador_disparos)++;
        
        // Processar PAR - no rjd, I e J do mesmo par SEMPRE se sobrepõem
        FormaGeometrica forma_j = removeFila(arena);
        FormaGeometrica forma_i = removeFila(arena);
        
        // Comparar áreas: maior esmaga menor
        double area_i = forma_get_area(forma_i);
        double area_j = forma_get_area(forma_j);
        
        if (area_i < area_j) {
            // J (maior) esmaga I (menor)
            *pontuacao_total += area_i;
            (*total_esmagados)++;
            fprintf(log_txt, "SOBREPOSICAO (RJD PAR): Forma I id:%d (area %.2f) esmagada pela Forma J id:%d (area %.2f).\n",
                forma_get_id(forma_i), area_i, forma_get_id(forma_j), area_j);
            
            double x_esmag = forma_get_x(forma_i);
            double y_esmag = forma_get_y(forma_i);
            (*num_anotacoes_esmag)++;
            *array_anotacoes_esmag = realloc(*array_anotacoes_esmag, (*num_anotacoes_esmag) * sizeof(AnotacaoEsmagamento));
            AnotacaoEsmagamento* nova_anot = &((*array_anotacoes_esmag)[(*num_anotacoes_esmag) - 1]);
            nova_anot->x = x_esmag;
            nova_anot->y = y_esmag;
            
            destruir_forma_completa(forma_i);
            insertFila(fila_chao, forma_j);
        } else {
            // I >= J: I (maior) esmaga J (menor)
            *pontuacao_total += area_j;
            (*total_esmagados)++;
            fprintf(log_txt, "SOBREPOSICAO (RJD PAR): Forma J id:%d (area %.2f) esmagada pela Forma I id:%d (area %.2f).\n",
                forma_get_id(forma_j), area_j, forma_get_id(forma_i), area_i);
            
            double x_esmag = forma_get_x(forma_j);
            double y_esmag = forma_get_y(forma_j);
            (*num_anotacoes_esmag)++;
            *array_anotacoes_esmag = realloc(*array_anotacoes_esmag, (*num_anotacoes_esmag) * sizeof(AnotacaoEsmagamento));
            AnotacaoEsmagamento* nova_anot = &((*array_anotacoes_esmag)[(*num_anotacoes_esmag) - 1]);
            nova_anot->x = x_esmag;
            nova_anot->y = y_esmag;
            
            destruir_forma_completa(forma_j);
            insertFila(fila_chao, forma_i);
        }
        
        dx_atual += ix;
        dy_atual += iy;
        disparos_efetuados += 2;
    }
    
    if (log_txt) {
        fprintf(log_txt, "Rajada de disparos executada. %d formas disparadas em pares.\n", disparos_efetuados);
    }
}

static void tratar_comando_calc(FILA arena, Chao chao, double* pontuacao_total,
                                int* contador_esmagados, int* contador_clonados,
                                AnotacaoEsmagamento** array_anotacoes_esmag, int* num_anotacoes_esmag,
                                int* proximo_id_clone,
                                FILE* log_txt) {
    if (log_txt) {
        fprintf(log_txt, "Processando figuras da arena (pares consecutivos)...\n");
    }

    double area_esmagada_round = 0;
    FILA fila_retorno = criarFila();
    FILA fila_clones = criarFila();

    if (fila_vazia(arena)) {
        fprintf(log_txt, "Processamento das formas concluído.\n");
        destruirFila(fila_retorno);
        destruirFila(fila_clones);
        return;
    }

    // Converter arena para array para processar pares (i, i+1)
    const int MAX_FORMAS = 100;
    FormaGeometrica formas[MAX_FORMAS];
    int n = 0;
    
    while (!fila_vazia(arena) && n < MAX_FORMAS) {
        formas[n] = removeFila(arena);
        n++;
    }
    
    // Processar pares consecutivos (0,1), (2,3), (4,5), etc.
    for (int i = 0; i + 1 < n; i += 2) {
        FormaGeometrica forma_i = formas[i];
        FormaGeometrica forma_j = formas[i + 1];
        
        bool sobrepoe = formas_se_sobrepoem(forma_i, forma_j);
        
        if (sobrepoe) {
            double area_i = forma_get_area(forma_i);
            double area_j = forma_get_area(forma_j);
            
            if (area_i < area_j) {
                // Forma I é menor: esmagada
                area_esmagada_round += area_i;
                (*contador_esmagados)++;
                fprintf(log_txt, "SOBREPOSICAO: Forma I (id %d, area %.2f) esmagada pela Forma J (id %d, area %.2f).\n",
                    forma_get_id(forma_i), area_i, forma_get_id(forma_j), area_j);
                
                double x_esmag = forma_get_x(forma_i);
                double y_esmag = forma_get_y(forma_i);
                (*num_anotacoes_esmag)++;
                *array_anotacoes_esmag = realloc(*array_anotacoes_esmag, (*num_anotacoes_esmag) * sizeof(AnotacaoEsmagamento));
                AnotacaoEsmagamento* nova_anot = &((*array_anotacoes_esmag)[(*num_anotacoes_esmag) - 1]);
                nova_anot->x = x_esmag;
                nova_anot->y = y_esmag;
                
                destruir_forma_completa(forma_i);
                formas[i] = NULL;
                
            } else {
                // Forma I >= J: I altera J e é clonada
                fprintf(log_txt, "SOBREPOSICAO: Forma I (id %d) altera Forma J (id %d) e eh clonada.\n",
                    forma_get_id(forma_i), forma_get_id(forma_j));
                
                const char* cor_i = forma_get_cor_preenchimento(forma_i);
                if (cor_i) forma_set_cor_borda(forma_j, cor_i);
                
                FormaGeometrica clone_i = forma_clonar(forma_i, proximo_id_clone);
                if (clone_i) {
                    insertFila(fila_clones, clone_i);
                    PILHA pilha_gestao = leitor_geo_get_pilha_gestao(chao);
                    push(pilha_gestao, clone_i);
                    (*contador_clonados)++;
                }
            }
        } else {
            fprintf(log_txt, "SEM SOBREPOSICAO: As formas com id %d e %d retornam ao chao.\n",
                forma_get_id(forma_i), forma_get_id(forma_j));
        }
    }
    
    // Retornar formas não esmagadas ao chão
    for (int i = 0; i < n; i++) {
        if (formas[i] != NULL) {
            insertFila(fila_retorno, formas[i]);
        }
    }
    
    // Adicionar clones
    while (!fila_vazia(fila_clones)) {
        insertFila(fila_retorno, removeFila(fila_clones));
    }

    // Retorna todas as formas ao chão
    FILA fila_do_chao = leitor_geo_get_fila_principal(chao);
    while (!fila_vazia(fila_retorno)) {
        FormaGeometrica forma = removeFila(fila_retorno);
        if (forma) insertFila(fila_do_chao, forma);
    }

    destruirFila(fila_retorno);
    destruirFila(fila_clones);

    *pontuacao_total += area_esmagada_round;
    fprintf(log_txt, "Fim do round. Area total esmagada no round: %.2f. Area total acumulada: %.2f\n", area_esmagada_round, *pontuacao_total);
}



static double forma_get_area(FormaGeometrica forma) {
        if (forma == NULL) {
        return 0.0;
    }

    ShapeType tipo = forma_get_tipo(forma);
    void* dados = forma_get_dados(forma);

    switch (tipo){
        case CIRCULO:
            return circulo_get_area((Circulo)dados);
        case RETANGULO:
            return retangulo_get_area((Retangulo)dados);
        case LINHA:
            return linha_get_area((Linha)dados);
        case TEXTO:
        return texto_get_area((Texto)dados);
        case ESTILO_TEXTO:
            return 0.0;
        default:
            return printf("Tipo de forma desconhecido para cálculo de área.\n"), 0.0;
    }
}


static bool circulo_circulo_sobrepoe(FormaGeometrica c1_forma, FormaGeometrica c2_forma) {
    void* c1 = forma_get_dados(c1_forma);
    void* c2 = forma_get_dados(c2_forma);
    double x1 = circulo_get_x(c1), y1 = circulo_get_y(c1), r1 = circulo_get_raio(c1);
    double x2 = circulo_get_x(c2), y2 = circulo_get_y(c2), r2 = circulo_get_raio(c2);

    double distSq = pow(x1 - x2, 2) + pow(y1 - y2, 2);
    double radiiSumSq = pow(r1 + r2, 2);

    return distSq <= radiiSumSq;
}

static bool retangulo_retangulo_sobrepoe(FormaGeometrica r1_forma, FormaGeometrica r2_forma) {
    void* r1 = forma_get_dados(r1_forma);
    void* r2 = forma_get_dados(r2_forma);
    double x1 = retangulo_get_x(r1), y1 = retangulo_get_y(r1);
    double w1 = retangulo_get_larg(r1), h1 = retangulo_get_altura(r1);
    double x2 = retangulo_get_x(r2), y2 = retangulo_get_y(r2);
    double w2 = retangulo_get_larg(r2), h2 = retangulo_get_altura(r2);

    bool semSobreposicaoX = (x1 + w1 <= x2) || (x1 >= x2 + w2);
    bool semSobreposicaoY = (y1 + h1 <= y2) || (y1 >= y2 + h2);

    if (semSobreposicaoX || semSobreposicaoY) {
        return false;
    }
    return true;
}


static bool circulo_retangulo_sobrepoe(FormaGeometrica circ_forma, FormaGeometrica rect_forma) {
    void* circ = forma_get_dados(circ_forma);
    void* rect = forma_get_dados(rect_forma);
    double cx = circulo_get_x(circ), cy = circulo_get_y(circ), cr = circulo_get_raio(circ);
    double rx = retangulo_get_x(rect), ry = retangulo_get_y(rect);
    double rw = retangulo_get_larg(rect), rh = retangulo_get_altura(rect);
    double rx2 = rx + rw;
    double ry2 = ry + rh;

    double clampX = (cx < rx) ? rx : (cx > rx2) ? rx2 : cx;
    double clampY = (cy < ry) ? ry : (cy > ry2) ? ry2 : cy;

    double distX = cx - clampX;
    double distY = cy - clampY;
    double distanceSquared = (distX * distX) + (distY * distY);

    return distanceSquared <= (cr * cr);
}

static bool texto_get_segmento(FormaGeometrica texto_forma, double* x1, double* y1, double* x2, double* y2) {
    if (!texto_forma) return false;
    void* texto = forma_get_dados(texto_forma);

    double xt = texto_get_x(texto);
    double yt = texto_get_y(texto);
    char ancora = texto_get_ancora(texto);
    const char* conteudo = texto_get_conteudo(texto);
    double len = (conteudo != NULL) ? strlen(conteudo) : 0;
    double cl = 10.0 * len; 

    if (ancora == 'i') {
        *x1 = xt; *y1 = yt;
        *x2 = xt + cl; *y2 = yt;
    } else if (ancora == 'm') { 
        *x1 = xt - cl / 2.0; *y1 = yt;
        *x2 = xt + cl / 2.0; *y2 = yt;
    } else if (ancora == 'f') { 
        *x1 = xt - cl; *y1 = yt;
        *x2 = xt; *y2 = yt;
    } else {
        return false;
    }
    return true;
}
static int orientacao(double px, double py, double qx, double qy, double rx, double ry) {
    double val = (qy - py) * (rx - qx) - (qx - px) * (ry - qy);
    if (fabs(val) < 1e-9) return 0;
    return (val > 0) ? 1 : 2;
}

static bool no_segmento(double px, double py, double qx, double qy, double rx, double ry) {
    return (qx <= fmax(px, rx) && qx >= fmin(px, rx) &&
            qy <= fmax(py, ry) && qy >= fmin(py, ry));
}

static bool linha_linha_sobrepoe(double p1x, double p1y, double q1x, double q1y, double p2x, double p2y, double q2x, double q2y) {
    int o1 = orientacao(p1x, p1y, q1x, q1y, p2x, p2y);
    int o2 = orientacao(p1x, p1y, q1x, q1y, q2x, q2y);
    int o3 = orientacao(p2x, p2y, q2x, q2y, p1x, p1y);
    int o4 = orientacao(p2x, p2y, q2x, q2y, q1x, q1y);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && no_segmento(p1x, p1y, p2x, p2y, q1x, q1y)) return true;
    if (o2 == 0 && no_segmento(p1x, p1y, q2x, p2y, q1x, q1y)) return true;
    if (o3 == 0 && no_segmento(p2x, p2y, p1x, p1y, q2x, q2y)) return true;
    if (o4 == 0 && no_segmento(p2x, p2y, q1x, q1y, q2x, q2y)) return true;

    return false;
}

static double ponto_segmento_dist_quadrada(double px, double py, double ax, double ay, double bx, double by) {
    double l2 = pow(bx - ax, 2) + pow(by - ay, 2);
    if (l2 == 0.0) return pow(px - ax, 2) + pow(py - ay, 2);
    double t = ((px - ax) * (bx - ax) + (py - ay) * (by - ay)) / l2;
    t = fmax(0.0, fmin(1.0, t)); 
    double projX = ax + t * (bx - ax);
    double projY = ay + t * (by - ay);
    return pow(px - projX, 2) + pow(py - projY, 2);
}

static bool circulo_linha_sobrepoe(FormaGeometrica circ_forma, double lx1, double ly1, double lx2, double ly2) {
    void* circ = forma_get_dados(circ_forma);
    double cx = circulo_get_x(circ), cy = circulo_get_y(circ), cr = circulo_get_raio(circ);

    double distSq = ponto_segmento_dist_quadrada(cx, cy, lx1, ly1, lx2, ly2);

    return distSq <= (cr * cr);
}

static bool retangulo_linha_sobrepoe(FormaGeometrica rect_forma, double lx1, double ly1, double lx2, double ly2) {
    void* rect = forma_get_dados(rect_forma);
    double rx = retangulo_get_x(rect), ry = retangulo_get_y(rect);
    double rw = retangulo_get_larg(rect), rh = retangulo_get_altura(rect);
    double rx2 = rx + rw, ry2 = ry + rh;

    bool p1_dentro = (lx1 >= rx && lx1 <= rx2 && ly1 >= ry && ly1 <= ry2);
    bool p2_dentro = (lx2 >= rx && lx2 <= rx2 && ly2 >= ry && ly2 <= ry2);
    if (p1_dentro || p2_dentro) return true;

    if (linha_linha_sobrepoe(lx1, ly1, lx2, ly2, rx, ry, rx2, ry)) return true;
    if (linha_linha_sobrepoe(lx1, ly1, lx2, ly2, rx2, ry, rx2, ry2)) return true;
    if (linha_linha_sobrepoe(lx1, ly1, lx2, ly2, rx2, ry2, rx, ry2)) return true;
    if (linha_linha_sobrepoe(lx1, ly1, lx2, ly2, rx, ry2, rx, ry)) return true;

    return false;
}


static bool formas_se_sobrepoem(FormaGeometrica forma1, FormaGeometrica forma2) {
    // Validação: verifica se ambas as formas são válidas
    if (!forma1 || !forma2) {
        return false;
    }

    // Obtém os tipos das formas para determinar o algoritmo de sobreposição
    ShapeType tipo1 = forma_get_tipo(forma1);
    ShapeType tipo2 = forma_get_tipo(forma2);

    // Variáveis para armazenar coordenadas de segmentos (linhas ou textos tratados como segmentos)
    double l1x1=0, l1y1=0, l1x2=0, l1y2=0;
    double l2x1=0, l2y1=0, l2x2=0, l2y2=0;
    bool forma1_eh_segmento = false;
    bool forma2_eh_segmento = false;

    // Extrai coordenadas de segmento da forma1 (se for LINHA ou TEXTO)
    if (tipo1 == LINHA) {
        void* d1 = forma_get_dados(forma1);
        l1x1 = linha_get_x1(d1); l1y1 = linha_get_y1(d1);
        l1x2 = linha_get_x2(d1); l1y2 = linha_get_y2(d1);
        forma1_eh_segmento = true;
    } else if (tipo1 == TEXTO) {
        // TEXTO pode ser tratado como segmento se tiver uma representação linear
        forma1_eh_segmento = texto_get_segmento(forma1, &l1x1, &l1y1, &l1x2, &l1y2);
    }

    // Extrai coordenadas de segmento da forma2 (se for LINHA ou TEXTO)
    if (tipo2 == LINHA) {
        void* d2 = forma_get_dados(forma2);
        l2x1 = linha_get_x1(d2); l2y1 = linha_get_y1(d2);
        l2x2 = linha_get_x2(d2); l2y2 = linha_get_y2(d2);
        forma2_eh_segmento = true;
    } else if (tipo2 == TEXTO) {
        forma2_eh_segmento = texto_get_segmento(forma2, &l2x1, &l2y1, &l2x2, &l2y2);
    }

    // Dispatcher: escolhe a função de sobreposição baseada nos tipos das formas
    // Caso 1: forma1 é CIRCULO
    if (tipo1 == CIRCULO) {
        if (tipo2 == CIRCULO) {
            return circulo_circulo_sobrepoe(forma1, forma2);
        } else if (tipo2 == RETANGULO) {
            return circulo_retangulo_sobrepoe(forma1, forma2);
        } else if (forma2_eh_segmento) {
            // Círculo com linha ou texto (tratado como segmento)
            return circulo_linha_sobrepoe(forma1, l2x1, l2y1, l2x2, l2y2);
        }
    } 
    // Caso 2: forma1 é RETANGULO
    else if (tipo1 == RETANGULO) {
        if (tipo2 == CIRCULO) {
            // Inverte ordem para reutilizar função círculo-retângulo
            return circulo_retangulo_sobrepoe(forma2, forma1); 
        } else if (tipo2 == RETANGULO) {
            return retangulo_retangulo_sobrepoe(forma1, forma2);
        } else if (forma2_eh_segmento) {
            return retangulo_linha_sobrepoe(forma1, l2x1, l2y1, l2x2, l2y2);
        }
    } 
    // Caso 3: forma1 é LINHA ou TEXTO (tratado como segmento)
    else if (forma1_eh_segmento) {
        if (tipo2 == CIRCULO) {
            return circulo_linha_sobrepoe(forma2, l1x1, l1y1, l1x2, l1y2); 
        } else if (tipo2 == RETANGULO) {
            return retangulo_linha_sobrepoe(forma2, l1x1, l1y1, l1x2, l1y2); 
        } else if (forma2_eh_segmento) {
            // Segmento com segmento (linha-linha, linha-texto, texto-texto)
            return linha_linha_sobrepoe(l1x1, l1y1, l1x2, l1y2, l2x1, l2y1, l2x2, l2y2);
        }
    }

    // Caso não tratado: não há sobreposição
    return false;
}