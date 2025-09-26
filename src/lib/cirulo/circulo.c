#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#define pi 3.14

struct Circulo{
    int id;
    int x;
    int y;
    double r;
    double area;
    char corp[8];
    char corb[8];
};

static double CalcArea(double r){
    if(r<0){
        return 0;
    }
    return pi * r * r;
}


CIRCULO CriarCirc(int id, int x, int y, double r, const char* corb, const char* corp){
    CIRCULO c = (CIRCULO)malloc(sizeof(struct Circulo));
    if(c == NULL){
        return NULL;
    }
    c->id = id;
    c->x = x;
    c->y = y;
    c->r = r;
    strcpy(c->corb, corb);
    strcpy(c->corp, corp);
    c->area = CalcArea(c->r);

    return c;
}

void DestruirCirc(CIRCULO c){
    if(c != NULL){
        free(c);
    }
}

int circulo_get_id(const CIRCULO c) {
    return (c != NULL) ? c->id : -1;
}

int circulo_get_x(const CIRCULO c) {
    return (c != NULL) ? c->x : 0;
}

int circulo_get_y(const CIRCULO c) {
    return (c != NULL) ? c->y : 0;
}

double circulo_get_raio(const CIRCULO c) {
    return (c != NULL) ? c->r : 0.0;
}

double circulo_get_area(const CIRCULO c) {
    return (c != NULL) ? c->area : 0.0;
}

const char* circulo_get_corb(const CIRCULO c) {
    return (c != NULL) ? c->corb : "invalido";
}

const char* circulo_get_corp(const CIRCULO c) {
    return (c != NULL) ? c->corp : "invalido";
}

