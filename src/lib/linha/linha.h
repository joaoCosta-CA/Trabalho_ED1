#ifndef LINHA_H
#define LINHA_H

typedef void* Linha;


/*
    arquivo destina para a organização de todas as funções e modificações para a forma linha
*/

Linha criarLinha(int id, float x1, float y1, float x2, float y2, char *cor);
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


 /*--------------Funções para acessar todos os parametros da Linha ----------------------*/
 int linha_get_id(const Linha l);
 float linha_get_x1(const Linha l);
 float linha_get_x2(const Linha l);
 float linha_get_y1(const Linha l);
 float linha_get_y2(const Linha l);
 double linha_get_area(const Linha l);
 const char* linha_get_cor(const Linha l);
 /*---------------------------------------------------------------------------------------*/

#endif