#ifndef DISPADOR_H
#define DISPADOR_H

#include "../fila/fila.h"
#include "lib/formas/formas.h"
#include "../carregadores/carregador.h"

// Ponteiro opaco para o Disparador
typedef void* Disp;

// --- FUNÇÕES DE CICLO DE VIDA ---
Disp criar_disparador(int id, double x, double y);
void destruir_disparador(Disp disp);

// --- FUNÇÕES DE CONFIGURAÇÃO ---
void posicionar_disparador(Disp disp, double x, double y);
// A assinatura agora usa o TAD Carregador, tornando o código mais abstrato
void anexar_carregadores(Disp disp, Carregador carregador_esq, Carregador carregador_dir);

// --- FUNÇÕES DE AÇÃO ---
void shift_carga(Disp disp, char lado, int n);
void disparar_forma(Disp disp, double dx, double dy, FILA arena);
int rajada_de_disparos(Disp disp, char lado, double dx, double dy, double ix, double iy, FILA arena);

// --- FUNÇÕES DE ACESSO (GETTERS) ---
int disparador_get_id(Disp disp);
double disparador_get_x(Disp disp);
double disparador_get_y(Disp disp);
FormaGeometrica* disparador_get_em_disparo(Disp disp);

#endif