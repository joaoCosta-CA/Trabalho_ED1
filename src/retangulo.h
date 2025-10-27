#ifndef RETANGULO_H
#define RETANGULO_H

typedef void* Retangulo;

/*
    arquivo destina para a organização de todas as funções e modificações para a forma retangulo
*/

Retangulo criarRec(int id, float x, float y, double w, double h, const char* corb, const char* corp);
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

/**
 * @brief Retorna o identificador inteiro do retângulo.
 *
 * @param r Estrutura Retangulo (passada por valor) da qual se deseja obter o id.
 * @return int Identificador associado ao retângulo.
 */
int retangulo_get_id(const Retangulo r);

/**
 * @brief Retorna a coordenada X (posição horizontal) do retângulo.
 *
 * @param r Estrutura Retangulo (passada por valor) da qual se deseja obter a coordenada X.
 * @return float Valor da coordenada X.
 */
float retangulo_get_x(const Retangulo r);

/**
 * @brief Retorna a coordenada Y (posição vertical) do retângulo.
 *
 * @param r Estrutura Retangulo (passada por valor) da qual se deseja obter a coordenada Y.
 * @return float Valor da coordenada Y.
 */
float retangulo_get_y(const Retangulo r);

/**
 * @brief Retorna a largura do retângulo.
 *
 * @param r Estrutura Retangulo (passada por valor) da qual se deseja obter a largura.
 * @return double Largura do retângulo.
 */
double retangulo_get_larg(const Retangulo r);

/**
 * @brief Retorna a altura do retângulo.
 *
 * @param r Estrutura Retangulo (passada por valor) da qual se deseja obter a altura.
 * @return double Altura do retângulo.
 */
double retangulo_get_altura(const Retangulo r);

/**
 * @brief Retorna a cor de preenchimento (fill) do retângulo como string.
 *
 * @param r Estrutura Retangulo (passada por valor) da qual se deseja obter a cor de preenchimento.
 * @return const char* Ponteiro para a string que representa a cor de preenchimento.
 *         A string não deve ser modificada pelo chamador e permanece válida
 *         conforme o contrato da API (por ex., enquanto o objeto Retangulo existir).
 */
const char* retangulo_get_corp(const Retangulo r);

/**
 * @brief Retorna a cor da borda (stroke) do retângulo como string.
 *
 * @param r Estrutura Retangulo (passada por valor) da qual se deseja obter a cor da borda.
 * @return const char* Ponteiro para a string que representa a cor da borda.
 *         A string não deve ser modificada pelo chamador e permanece válida
 *         conforme o contrato da API (por ex., enquanto o objeto Retangulo existir).
 */
const char* retangulo_get_corb(const Retangulo r);

/**
 * @brief Calcula e retorna a área do retângulo.
 *
 * @param r Estrutura Retangulo (passada por valor) cujas dimensões serão usadas no cálculo.
 * @return double Área calculada (largura * altura).
 */
double retangulo_get_area(const Retangulo r);

/*-----------FUNÇÕES SETTERS-----------------*/

/**
 * Define a coordenada X do retângulo.
 *
 * Ajusta a posição horizontal (x) do retângulo para o valor especificado.
 *
 * @param r  Instância do retângulo a ser modificada.
 * @param x  Nova coordenada X (unidades do sistema de coordenadas utilizado).
 *
 * @return void
 */
void retangulo_set_x(Retangulo r, float x);

/**
 * Define a coordenada Y do retângulo.
 *
 * Ajusta a posição vertical (y) do retângulo para o valor especificado.
 *
 * @param r  Instância do retângulo a ser modificada.
 * @param y  Nova coordenada Y (unidades do sistema de coordenadas utilizado).
 *
 * @return void
 */
void retangulo_set_y(Retangulo r, float y);

/**
 * Define a cor de preenchimento do retângulo.
 *
 * Atualiza a cor interna (preenchimento) do retângulo usando a string fornecida.
 * A string 'corp' deve representar uma cor (por exemplo, nomes de cor ou códigos hexadecimais),
 * conforme o formato esperado pela implementação.
 *
 * @param r     Instância do retângulo a ser modificada.
 * @param corp  String que descreve a cor de preenchimento.
 *
 * @return void
 */
void retangulo_set_corp(Retangulo r, const char* corp);

/**
 * Define a cor da borda do retângulo.
 *
 * Atualiza a cor da borda (contorno) do retângulo usando a string fornecida.
 * A string 'corb' deve representar uma cor (por exemplo, nomes de cor ou códigos hexadecimais),
 * conforme o formato esperado pela implementação.
 *
 * @param r     Instância do retângulo a ser modificada.
 * @param corb  String que descreve a cor da borda.
 *
 * @return void
 */
void retangulo_set_corb(Retangulo r, const char* corb);

#endif