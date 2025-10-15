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

/*----------FUNÇÕES GETTERS------------*/

// Retorna o valor do id da forma
int retangulo_get_id(const Retangulo r);

// Retorna o valor de x do Retangulo criado
float retangulo_get_x(const Retangulo r);

// Retorna o valor de y do Retangulo criado
float retangulo_get_y(const Retangulo r);

// Retorna o valor da largura 'w' do Retangulo criado
double retangulo_get_larg(const Retangulo r);

// Retorna o valor da altura 'h' do Retangulo criado
double retangulo_get_altura(const Retangulo r);

// Retorna uma string em hexadecimal que indica a cor de preenchimento
const char* retangulo_get_corp(const Retangulo r);

// Retorna uma string em hexadecimal que indica a cor da borda
const char* retangulo_get_corb(const Retangulo r);

// Retorna o valor da área do retangulo criado
double retangulo_get_area(const Retangulo r);

/*-----------FUNÇÕES SETTERS-----------------*/

// Define o valor de x do retângulo
void retangulo_set_x(Retangulo r, float x);

// Define o valor de y do retângulo
void retangulo_set_y(Retangulo r, float y);

// Define a cor de preenchimento do retângulo
void retangulo_set_corp(Retangulo r, char* corp);

// Define a cor da borda do retângulo
void retangulo_set_corb(Retangulo r, char* corb);

#endif