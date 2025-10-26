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

/**
 * @brief Libera os recursos associados a uma Linha.
 *
 * Esta função destrói a estrutura representada por 'l', liberando a memória
 * e quaisquer recursos internos alocados para a Linha.
 *
 * @param l Handle/ponteiro para a Linha a ser destruída. Se 'l' for NULL,
 *          a função não realiza nenhuma ação.
 *
 * @pre 'l' deve ter sido obtido previamente por uma função de criação ou
 *      outra rotina que retorne um objeto Linha válido.
 * @post Os recursos associados a 'l' foram liberados e o handle torna-se
 *       inválido; não deve ser utilizado após a chamada.
 *
 */
 void destruirLinha(Linha l);


 /*--------------FUNCÇÕES GETTERS ----------------------*/

/**
 * @brief Retorna o identificador da linha.
 *
 * @param l Instância da Linha cujo identificador será obtido. Deve representar
 *          uma linha válida.
 * @return int Identificador (ID) associado à linha.
 *
 */
int linha_get_id(const Linha l);
 
/**
 * @brief Obtém a coordenada X do primeiro ponto da linha.
 *
 * @param l Instância da Linha da qual se deseja a coordenada X1.
 * @return float Valor da coordenada X do primeiro ponto.
 *
 */
float linha_get_x1(const Linha l);
 
/**
 * @brief Obtém a coordenada Y do primeiro ponto da linha.
 *
 * @param l Instância da Linha da qual se deseja a coordenada Y1.
 * @return float Valor da coordenada Y do primeiro ponto.
 *
 */
float linha_get_y1(const Linha l);
 
/**
 * @brief Obtém a coordenada X do segundo ponto da linha.
 *
 * @param l Instância da Linha da qual se deseja a coordenada X2.
 * @return float Valor da coordenada X do segundo ponto.
 *
 */
float linha_get_x2(const Linha l);
 
/**
 * @brief Obtém a coordenada Y do segundo ponto da linha.
 *
 * @param l Instância da Linha da qual se deseja a coordenada Y2.
 * @return float Valor da coordenada Y do segundo ponto.
 *
 */
float linha_get_y2(const Linha l);
 
/**
 * @brief Calcula e retorna a "área" associada à linha.
 *
 * @param l Instância da Linha para a qual a área será calculada.
 * @return double Valor da área associada à linha (conforme definição usada
 *                pela aplicação; por exemplo pode ser 0 para uma linha pura
 *                ou outra métrica definida pelo domínio).
 *
 */
double linha_get_area(const Linha l);
 
/**
 * @brief Retorna a cor associada à linha.
 *
 * @param l Instância da Linha da qual se obtém a cor.
 * @return const char* String imutável contendo a cor (por exemplo nome ou código).
 *
 */
const char* linha_get_cor(const Linha l);

 /*--------------FUNÇÕES SETTERS ----------------------*/

/**
 * @brief Define a coordenada X do primeiro ponto da linha.
 *
 * @param l Instância da Linha cujo X1 será atualizado.
 * @param x1 Novo valor da coordenada X1.
 *
 * @note Comportamento indefinido se 'l' não for uma instância válida.
 */
void linha_set_x1(Linha l, float x1);

/**
 * @brief Define a coordenada Y do primeiro ponto da linha.
 *
 * @param l Instância da Linha cujo Y1 será atualizado.
 * @param y1 Novo valor da coordenada Y1.
 *
 */
void linha_set_y1(Linha l, float y1);

/**
 * @brief Define a coordenada X do segundo ponto da linha.
 *
 * @param l Instância da Linha cujo X2 será atualizado.
 * @param x2 Novo valor da coordenada X2.
 *
 */
void linha_set_x2(Linha l, float x2);

/**
 * @brief Define a coordenada Y do segundo ponto da linha.
 *
 * @param l Instância da Linha cujo Y2 será atualizado.
 * @param y2 Novo valor da coordenada Y2.
 *
 */
void linha_set_y2(Linha l, float y2);

/**
 * @brief Define a cor associada à linha.
 *
 * @param l Instância da Linha cuja cor será atualizada.
 * @param cor String representando a cor (por exemplo nome ou código).
 *
 */
void linha_set_cor(Linha l, const char* cor);

#endif