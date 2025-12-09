#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "disparador.h"
#include "leitor_geo.h"
#include "linha.h"
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "carregador.h"
#include "leitor_geo.h"

typedef struct {
    int id;
    double x;
    double y;
    Carregador carga_esq;
    Carregador carga_dir;
    FormaGeometrica* em_disparo;
} DisparadorStruct;

Disp criar_disparador(int id, double x, double y) {
    DisparadorStruct *d = malloc(sizeof(DisparadorStruct));
    if (d == NULL) return NULL;

    d->id = id;
    d->x = x;
    d->y = y;
    d->carga_esq = NULL;
    d->carga_dir = NULL;
    d->em_disparo = NULL;

    return (Disp)d;
}

void destruir_disparador(Disp disp) {
    if (disp != NULL) {
        free(disp);
    }
}

void posicionar_disparador(Disp disp, double x, double y) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    d->x = x;
    d->y = y;
}

void anexar_carregadores(Disp disp, Carregador carregador_esq, Carregador carregador_dir) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    if (d == NULL) return;

    d->carga_esq = carregador_esq;

    d->carga_dir = carregador_dir;

}

void shift_carga(Disp disp, char lado, int n) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    if (d == NULL) return;

    for (int i = 0; i < n; i++) {
        FormaGeometrica nova_forma = NULL;
        char lado_usado = lado;
        
        // Verificar se carregador especificado está vazio, tentar o oposto
        if (lado_usado == 'd') {
            if (d->carga_dir == NULL || carregador_esta_vazio(d->carga_dir)) {
                if (d->carga_esq != NULL && !carregador_esta_vazio(d->carga_esq)) {
                    lado_usado = 'e';
                } else {
                    break; // Ambos vazios
                }
            }
        } else if (lado_usado == 'e') {
            if (d->carga_esq == NULL || carregador_esta_vazio(d->carga_esq)) {
                if (d->carga_dir != NULL && !carregador_esta_vazio(d->carga_dir)) {
                    lado_usado = 'd';
                } else {
                    break; // Ambos vazios
                }
            }
        }

        if (lado_usado == 'd' && d->carga_dir != NULL) {
            nova_forma = carregador_retira_forma(d->carga_dir);
        } else if (lado_usado == 'e' && d->carga_esq != NULL) {
            nova_forma = carregador_retira_forma(d->carga_esq);
        }
        
        if (nova_forma == NULL) break;
        d->em_disparo = nova_forma;
    }
}

void disparar_forma(Disp disp, double dx, double dy, FILA arena) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    if (d == NULL || d->em_disparo == NULL) {
        return;
    }

    FormaGeometrica forma_disparada = d->em_disparo;

    void* dados_forma = forma_get_dados(forma_disparada);

    double pos_final_x = d->x + dx;
    double pos_final_y = d->y + dy;

    switch (forma_get_tipo(forma_disparada)) {
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
    d->em_disparo = NULL;
}


int rajada_de_disparos(Disp disp, char lado, double dx, double dy, double ix, double iy, FILA arena) {
    DisparadorStruct *d = (DisparadorStruct *)disp;
    if (d == NULL) return 0;

    Carregador carga_alvo = (lado == 'd') ? d->carga_dir : d->carga_esq;
    if (carga_alvo == NULL) return 0;

    // Collect all form pointers into array (LIFO order from stack)
    const int MAX_DISPAROS = 100;
    FormaGeometrica* formas[MAX_DISPAROS];
    int count = 0;
    
    while (!carregador_esta_vazio(carga_alvo) && count < MAX_DISPAROS) {
        shift_carga(disp, lado, 1);
        formas[count++] = d->em_disparo;
    }
    
    // REVERSE to get smallest first with smallest Y
    int disparos_executados = 0;
    for (int i = count - 1; i >= 0; i--) {
        d->em_disparo = formas[i];
        disparar_forma(disp, dx, dy, arena);
        dx += ix;
        dy += iy;
        disparos_executados++;
    }
    
    return disparos_executados;
}
int disparador_get_id(Disp disp) {
    return ((DisparadorStruct*)disp)->id;
}
double disparador_get_x(Disp disp) {
    return ((DisparadorStruct*)disp)->x;
}
double disparador_get_y(Disp disp) {
    return ((DisparadorStruct*)disp)->y;
}
FormaGeometrica* disparador_get_em_disparo(Disp disp) {
    return ((DisparadorStruct*)disp)->em_disparo;
}