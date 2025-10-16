#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disparador.h"
#include "lib/pilha/pilha.h"
#include "lib/fila/fila.h"
#include "lib/formas/formas.h"
#include "lib/circulo/circulo.h"
#include "lib/retangulo/retangulo.h"
#include "lib/linha/linha.h"
#include "lib/texto/texto.h"


typedef struct {
    int id;
    double x;
    double y;

    PILHA carga_esq;
    PILHA carga_dir;
    FormaGeometrica* em_disparo;
} DisparadorStruct;


// --- FUNÇÕES DE CICLO DE VIDA ---

Disp criar_disparador(int id, double x, double y) {
    DisparadorStruct *d = (DisparadorStruct *)malloc(sizeof(DisparadorStruct));
    if (d == NULL) {
        perror("Erro ao alocar memória para o disparador");
        return NULL;
    }

    d->id = id;
    d->x = x;
    d->y = y;
    d->carga_esq = criarPilha();
    d->carga_dir = criarPilha();
    d->em_disparo = NULL;

    if (d->carga_esq == NULL || d->carga_dir == NULL) {
        destruirPilha(d->carga_esq);
        destruirPilha(d->carga_dir);
        free(d);
        return NULL;
    }

    return (Disp)d;
}

void destruir_disparador(Disp disp) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    if (d == NULL) return;

    // As pilhas (carregadores) são destruídas.
    destruirPilha(d->carga_esq);
    destruirPilha(d->carga_dir);
    free(d);
}


// --- FUNÇÕES DE CONFIGURAÇÃO ---

void posicionar_disparador(Disp disp, double x, double y) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    if (d == NULL) return;
    d->x = x;
    d->y = y;
}

void anexar_carregadores(Disp disp, PILHA carregador_esq, PILHA carregador_dir) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    if (d == NULL) return;

    // Libera as pilhas vazias que foram criadas com o disparador
    destruirPilha(d->carga_esq);
    destruirPilha(d->carga_dir);

    // Anexa as novas pilhas (carregadores)
    d->carga_esq = carregador_esq;
    d->carga_dir = carregador_dir;
}


// --- FUNÇÕES DE AÇÃO ---

void shift_carga(Disp disp, char lado, int n) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    if (d == NULL) return;

    for (int i = 0; i < n; i++) {
        FormaGeometrica* nova_forma = NULL;

        if (lado == 'd') {
            if (pilha_vazia(d->carga_dir)) break; // Carga direita vazia, para o laço.
            
            nova_forma = (FormaGeometrica *)pop(d->carga_dir);
            
            if (d->em_disparo != NULL) {
                push(d->carga_esq, d->em_disparo);
            }

        } else if (lado == 'e') {
            if (pilha_vazia(d->carga_esq)) break; // Carga esquerda vazia, para o laço.
            
            nova_forma = (FormaGeometrica *)pop(d->carga_esq);

            if (d->em_disparo != NULL) {
                push(d->carga_dir, d->em_disparo);
            }
        } else {
            // Lado inválido, interrompe a operação.
            break;
        }
        
        d->em_disparo = nova_forma;
    }
}

void disparar_forma(Disp disp, double dx, double dy, FILA arena) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    if (d == NULL || d->em_disparo == NULL) {
        return; // Nada para disparar
    }

    FormaGeometrica* forma_disparada = d->em_disparo;
    void* dados_forma = forma_disparada->dados_da_forma;
    
    // Calcula a posição final da âncora
    double pos_final_x = d->x + dx;
    double pos_final_y = d->y + dy;

    // Atualiza as coordenadas da forma de acordo com seu tipo
    switch (forma_disparada->tipo) {
        case CIRCULO:
            circulo_set_x(dados_forma, pos_final_x);
            circulo_set_y(dados_forma, pos_final_y);
            break;
        case RETANGULO:
            retangulo_set_x(dados_forma, pos_final_x);
            retangulo_set_y(dados_forma, pos_final_y);
            break;
        case TEXTO:
            texto_set_x(dados_forma, pos_final_x);
            texto_set_y(dados_forma, pos_final_y);
            break;
        case LINHA: {
            double x1_orig = linha_get_x1(dados_forma);
            double y1_orig = linha_get_y1(dados_forma);
            double x2_orig = linha_get_x2(dados_forma);
            double y2_orig = linha_get_y2(dados_forma);

            // Translada a linha inteira mantendo sua orientação e tamanho
            double desloc_x = pos_final_x - x1_orig;
            double desloc_y = pos_final_y - y1_orig;

            linha_set_x1(dados_forma, x1_orig + desloc_x);
            linha_set_y1(dados_forma, y1_orig + desloc_y);
            linha_set_x2(dados_forma, x2_orig + desloc_x);
            linha_set_y2(dados_forma, y2_orig + desloc_y);
            break;
        }
        default:
            break;
    }

    insertFila(arena, forma_disparada);
    d->em_disparo = NULL; // Limpa a posição de disparo
}

void rajada_de_disparos(Disp disp, char lado, double dx, double dy, double ix, double iy, FILA arena) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    if (d == NULL) return;

    PILHA carga_alvo = (lado == 'd') ? d->carga_dir : d->carga_esq;

    // Continua enquanto houver formas no carregador
    while (!pilha_vazia(carga_alvo)) {
        shift_carga(disp, lado, 1);
        
        disparar_forma(disp, dx, dy, arena);

        dx += ix;
        dy += iy;
    }
}


// --- FUNÇÕES DE ACESSO (GETTERS) ---

int disparador_get_id(Disp disp) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    return (d != NULL) ? d->id : -1;
}

double disparador_get_x(Disp disp) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    return (d != NULL) ? d->x : 0.0;
}

double disparador_get_y(Disp disp) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    return (d != NULL) ? d->y : 0.0;
}

FormaGeometrica* disparador_get_em_disparo(Disp disp) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    return (d != NULL) ? d->em_disparo : NULL;
}