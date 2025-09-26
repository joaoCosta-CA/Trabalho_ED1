#ifndef CIRCULO_H
#define CIRCULO_H

/*
   aqruivo destina para todas as funções que gerenciam a criação e mudanças do objeto circulo 
*/

typedef void* CIRCULO;

CIRCULO CriarCirc(int id,int x, int y, double r, char* corb, char* corp);
/** 
 * @brief cria um circulo com os parametros fornecidos
 * @param id é um inteiro usado para identificar a forma criada
 * @param x inteiro utilizado para definir a posição horizontal no grafico
 * @param y inteiro utilizado para definir a posição horiznotal no grafico
 * @param r um numero double que irá definir o raio de criação do circulo
 * @param corb é a cor de preenchimento da borda do circulo (ex:#000000) 
 * @param corp é a cor de preenchimento da área interior do circulo (ex:#000000)
*/

CIRCULO CalcArea(double r);
/**
 * @brief função criada para calcular a área total de uma circunferência 
 * @param 'r' será o valor do raio do circulo 
 */
    


#endif