#ifndef CIRCULO_H
#define CIRCULO_H

/*
   aqruivo destina para todas as funções que gerenciam a criação e mudanças do objeto circulo 
*/

typedef void* Circulo;/*typedef de um ponteiro opaco para 'CIRCULO'*/

Circulo CriarCirc(int id, float x, float y, double r,const char* corb,const char* corp);
/** 
 * @brief cria um circulo com os parametros fornecidos
 * @param id é um inteiro usado para identificar a forma criada
 * @param x utilizado para definir a posição horizontal no grafico
 * @param y utilizado para definir a posição horiznotal no grafico
 * @param r um numero double que irá definir o raio de criação do circulo
 * @param corb é a cor de preenchimento da borda do circulo (ex:#000000) 
 * @param corp é a cor de preenchimento da área interior do circulo (ex:#000000)
*/

void DestruirCirc(Circulo c); 
/**      
 * @brief libera a memória alocada para o circulo
 * @param c, ponteiro para o circulo a ser destruído
 */

 /*-------grupo de função usados para acessar os valores do circulo criado---------*/
 int circulo_get_id(const Circulo c);
 float circulo_get_x(const Circulo c);
 float circulo_get_y(const Circulo c);
 double circulo_get_raio(const Circulo c);
 double circulo_get_area(const Circulo c);
 const char* circulo_get_corb(const Circulo c);
 const char* circulo_get_corp(const Circulo c);
 /*----------------------------------------------------------------------*/

#endif