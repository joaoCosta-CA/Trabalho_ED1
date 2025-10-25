#ifndef LINHA_H
#define LINHA_H

typedef void* Linha;


/*
    arquivo destina para a organização de todas as funções e modificações para a forma linha
*/

Linha criarLinha(int id, float x1, float y1, float x2, float y2, const char* cor);
/**
 * @brief cria uma linha com os pontos (x1,y1) e (x2,y2)
 * @param id, um valor int que identifica a linha criada
 * @param x1, é um valor que indica a posição horizontal do primeiro ponto da linha
 * @param y1, é um valor que indica a posição vertical do primeiro ponto da linha
 * @param x2, é um valor que indica a posição horizontal do segundo ponto da linha
 * @param y2, é um valor que indica a posição vertical do segundo ponto da linha
 * @param corp, é a cor que a linha terá no seu interior
 * @param corb, é a cor que a borda da linha deverá ter
 */

 void destruirLinha(Linha l);
/**
 * @brief libera a memória alocada para a linha
 * @param l, ponteiro para a linha a ser destruída
 */


 /*--------------FUNCÇÕES GETTERS ----------------------*/

// Retorna o id da linha
int linha_get_id(const Linha l);

// Retorna x1 do primeiro ponto
float linha_get_x1(const Linha l);

// Retorna y1 do primeiro ponto
float linha_get_y1(const Linha l);

// Retorna x2 do segundo ponto
float linha_get_x2(const Linha l);

// Retorna y2 do segundo ponto
float linha_get_y2(const Linha l);

// Retorna a área da linha (geralmente zero)
double linha_get_area(const Linha l);

// Retorna a cor da linha
const char* linha_get_cor(const Linha l);

 /*--------------FUNÇÕES SETTERS ----------------------*/

 //define o valor de x1 para a linha
 void linha_set_x1(Linha l, float x1);

 //define o valor de y1 para a linha
 void linha_set_y1(Linha l, float y1);

//define o valor de x2 para a linha
 void linha_set_x2(Linha l, float x2);

//define o valor de y2 para a linha
 void linha_set_y2(Linha l, float y2);

//define a cor da linha
 void linha_set_cor(Linha l, const char* cor);

#endif