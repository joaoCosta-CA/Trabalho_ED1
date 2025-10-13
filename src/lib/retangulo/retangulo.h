#ifndef RETANGULO_H
#define RETANGULO_H

typedef void* Retangulo;

/*
    arquivo destina para a organização de todas as funções e modificações para a forma retangulo
*/

Retangulo criarRec(int id, float x, float y, double w, double h, char* corp, char* corb);
/**
 * @brief cria um retangulo de área WxH 
 * @param id, um valor int que identifica o retangulo criado
 * @param w, é um valor que indica a largura da base do retangulo
 * @param h, é um valor que indica a altura que o retangulo tem que ter
 * @param corp, é a cor que o retangulo terá no seu interior
 * @param corb, é a cor que a borda do retangula deverá ter
 */

void destruirRec(Retangulo r);
/**
 * @brief libera a memória alocada para o retangulo
 * @param r, ponteiro para o retangulo a ser destruído
 */

/*----------Funções para acessar os valores do Retangulo criado------------*/
 int retangulo_get_id(const Retangulo r);/*pega o valor do id da forma*/
 float retangulo_get_x(const Retangulo r);/*pega o valor de x do Retangulo criado*/
 float retangulo_get_y(const Retangulo r);/*pega o valor de y do Ret*/
 double retangulo_get_larg(const Retangulo r);/*pega o valor de largura 'w' do Retangulo criado*/
 double retangulo_get_altura(const Retangulo r);/*pega o valor da altura 'h' do Retangulo criado*/
 const char* retangulo_get_corp(const Retangulo r);/*pega uma string em hexa-decimal que irá ditar a cor de preenchimento*/
 const char* retangulo_get_corb(const Retangulo r);/*pega uma string em hexa-decimal que irá ditar a cor de borda*/
 double retangulo_get_area(const Retangulo r);/*pega o valor da área do retangulo criado*/
 /*------------------------------------------------------------------------*/

#endif