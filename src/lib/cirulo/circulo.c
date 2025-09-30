#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#define pi 3.141592653589793

typedef struct{
    int id;
    float x;
    float y;
    double r;
    double area;
    char corp[32];
    char corb[32];
}Circulo;

static double CalcArea(double r){
    if(r<0){
        return 0;
    }
    return pi * r * r;
}


CIRCULO CriarCirc(int id, int x, int y, double r, const char* corb, const char* corp){
    Circulo* c = (Circulo*)malloc(sizeof(Circulo));
    if(c == NULL){
        return NULL;
    }
    c->id = id;
    c->x = x;
    c->y = y;
    c->r = r;
    c->area = CalcArea(c->r);
    strncpy(c->corb, corb, sizeof(c->corb) - 1);
    c->corb[sizeof(c->corb) - 1] = '\0';
    strncpy(c->corp, corp, sizeof(c->corp) - 1);
    c->corp[sizeof(c->corp) - 1] = '\0';

    return c;
}

void DestruirCirc(CIRCULO c_g){
    Circulo* c = (Circulo*)c_g;
    if(c != NULL){
        free(c);
    }
}

int circulo_get_id(const CIRCULO c_g) {
    const Circulo* c = (const Circulo*)c_g;
    return (c != NULL) ? c->id : -1;
}

int circulo_get_x(const CIRCULO c_g) {
    const Circulo* c = (const Circulo*)c_g;
    return (c != NULL) ? c->x : 0;
}

int circulo_get_y(const CIRCULO c_g) {
    const Circulo* c = (const Circulo*)c_g;
    return (c != NULL) ? c->y : 0;
}

double circulo_get_raio(const CIRCULO c_g) {
    const Circulo* c = (const Circulo*)c_g;
    return (c != NULL) ? c->r : 0.0;
}

double circulo_get_area(const CIRCULO c_g) {
    const Circulo* c = (const Circulo*)c_g;
    return (c != NULL) ? c->area : 0.0;
}

const char* circulo_get_corb(const CIRCULO c_g) {
    const Circulo* c = (const Circulo*)c_g;
    return (c != NULL) ? c->corb : "invalido";
}

const char* circulo_get_corp(const CIRCULO c_g) {
    const Circulo* c = (const Circulo*)c_g;
    return (c != NULL) ? c->corp : "invalido";
}

