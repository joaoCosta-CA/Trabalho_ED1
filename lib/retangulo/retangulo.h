#ifndef RETANGULO_H
#define RETANGULO_H

typedef void* Retangulo;

/*
    arquivo destina para a organização de todas as funções e modificações para a forma retangulo
*/

Retangulo criarRec(int id, int w, int h, char* corp, char* corb);
/**
 * @brief cria um retangulo de área WxH 
 * @param id, um valor int que identifica o retangulo criado
 * @param w, é um valor inteiro que indica a largura da base do retangulo
 * @param h, é um valor inteiro que indica a altura que o retangulo tem que ter
 * @param corp, é a cor que o retangulo terá no seu interior
 * @param corb, é a cor que a borda do retangula deverá ter
 */

#endif