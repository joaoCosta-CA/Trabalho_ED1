#ifndef FORMAS_H
#define FORMAS_H

enum FormaTipo{ CIRCULO, RETANGULO, LINHA, TEXTO, ESTILO_TEXTO};

typedef enum FormaTipo ShapeType;

typedef struct {
    ShapeType tipo;
    void *dados_da_forma;
} FormaGeometrica;

#endif