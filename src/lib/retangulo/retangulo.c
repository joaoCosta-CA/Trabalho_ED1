#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"

typedef struct{
    int id;
    float x;
    float y;
    double w;
    double h;
    double area;
    char corp[32];
    char corb[32];
}retangulo;

static double CalcArea(double w, double h){
    if(w<0 || h<0){
        return 0;
    }

    return w*h;
}

Retangulo criarRec(int id, float x, float y, double w, double h, char* corp, char* corb){
    retangulo* r = (retangulo*)malloc(sizeof(retangulo));
    if(r == NULL){
        return NULL;
    }

    r->id = id;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;
    r->area = CalcArea(w,h);
    strncpy(r->corb, corb, sizeof(r->corb) - 1);
    r->corb[sizeof(r->corb) - 1] = '\0';
    strncpy(r->corp, corp, sizeof(r->corp) - 1);
    r->corp[sizeof(r->corp) - 1] = '\0';

    return r;
}

void destruirRec(Retangulo r_g){
    retangulo* r = (retangulo*)r_g;
    if(r != NULL){
        free(r);
    }
}


int getIDr(const Retangulo r_g){
    const retangulo* r = (const retangulo*)r_g; 
    if(r == NULL)return -1;
    return r->id;
}

double getW(const Retangulo r_g){
    const retangulo* r = (const retangulo*)r_g; 
    if(r == NULL)return 0;
    return r->w;
}

double getH(const Retangulo r_g){
    const retangulo* r = (const retangulo*)r_g; 
    if(r == NULL)return 0;
    return r->h;
}

const char* getCorp(const Retangulo r_g){
    const retangulo* r = (const retangulo*)r_g; 
    if(r == NULL)return NULL;
    return r->corp;
}

const char* getCorb(const Retangulo r_g){
    const retangulo* r = (const retangulo*)r_g; 
    if(r == NULL)return NULL;
    return r->corb;
}

double getArear(const Retangulo r_g){
    const retangulo* r = (const retangulo*)r_g; 
    if(r == NULL)return 0.0;
    return r->area;
}


