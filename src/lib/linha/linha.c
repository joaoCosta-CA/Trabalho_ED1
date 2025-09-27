#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linha.h"

typedef struct{
    int id;
    int x1;
    int y1;
    int x2;
    int y2;
    double area;
    char corp[32];
    char corb[32];
}Linha;

static double CalcArea(const Linha* l){
    // Calcula o comprimento usando a fórmula da distância euclidiana
    double dx = l->x2 - l->x1;
    double dy = l->y2 - l->y1;
    double comprimento = sqrt(pow(dx, 2) + pow(dy, 2));

    // A área é 2.0 * comprimento, conforme o PDF 
    return 2.0 * comprimento;
}

LINHA criarLinha(int id, int x1, int y1, int x2, int y2, char* corp, char* corb){
    Linha* l = (Linha*)malloc(sizeof(Linha));
    if(l == NULL){
        return NULL;
    }

    l->id = id;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;
    l->area = CalcArea(l);
    strncpy(l->corp, corp, sizeof(l->corp) - 1);
    l->corp[sizeof(l->corp) - 1] = '\0';
    strncpy(l->corb, corb, sizeof(l->corb) - 1);
    l->corb[sizeof(l->corb) - 1] = '\0';

    return l;
}

void destruirLinha(LINHA l_g){
    Linha* l = (Linha*)l_g;
    if(l != NULL){
        free(l);
    }
}

int getIDl(const LINHA l_g){
    const Linha* l = (const Linha*)l_g;
    if (l == NULL)return -1;
    return l->id;
}

int getX1(const LINHA l_g){
    const Linha* l = (const Linha*)l_g;
    if(l == NULL)return 0;
    return l->x1;
}
int getX2(const LINHA l_g){
    const Linha* l = (const Linha*)l_g;
    if(l == NULL)return 0;
    return l->x2;
}

int getY1(const LINHA l_g){
    const Linha* l = (const Linha*)l_g;
    if(l == NULL)return 0;
    return l->y1;
}

int getY2(const LINHA l_g){
    const Linha* l = (const Linha*)l_g;
    if(l == NULL)return 0;
    return l->y2;
}

double getArea(const LINHA l_g){
    const Linha* l = (const Linha*)l_g;
    if(l == NULL)return 0;
    return l->area;
}

const char* getCorp(const LINHA l_g){
    const Linha* l = (const Linha*)l_g;
    if(l == NULL) return NULL;
    return l->corp;
}

const char* getCorb(const LINHA l_g){
    const Linha* l = (const Linha*)l_g;
    if(l == NULL) return NULL;
    return l->corb;
}