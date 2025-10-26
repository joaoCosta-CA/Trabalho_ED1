#ifndef FORMAS_H
#define FORMAS_H

/**
 * @enum FormaTipo
 * @brief Tipos de formas gráficos suportados pela biblioteca.
 *
 * Enumera os diferentes tipos de elementos gráficos que podem ser
 * criados e manipulados pela aplicação (formas geométricas e texto/estilo).
 *
 * Valores:
 *  - CIRCULO:      Representa um círculo.
 *  - RETANGULO:    Representa um retângulo.
 *  - LINHA:        Representa uma linha reta.
 *  - TEXTO:        Representa um elemento de texto a ser renderizado.
 *  - ESTILO_TEXTO: Representa propriedades de estilo de texto
 *                  (por exemplo fonte, tamanho, cor, alinhamento).
 */
enum FormaTipo{ CIRCULO, RETANGULO, LINHA, TEXTO, ESTILO_TEXTO};

typedef enum FormaTipo ShapeType;

#endif