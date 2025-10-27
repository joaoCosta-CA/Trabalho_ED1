#ifndef CIRCULO_H
#define CIRCULO_H

/*
   aqruivo destina para todas as funções que gerenciam a criação e mudanças do objeto circulo 
*/

typedef void* Circulo;/*typedef de um ponteiro opaco para 'CIRCULO'*/

Circulo CriarCirc(int id, float x, float y, double r, const char* corb, const char* corp);
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

 /*-------------------FUNÇÕES GETTERS------------------------------*/

/**
 * Obtém o identificador do círculo.
 *
 * @param c O círculo de onde o identificador será lido. A função não modifica este objeto.
 * @return O identificador inteiro associado ao círculo.
 */
 int circulo_get_id(const Circulo c);

/**
 * Obtém a coordenada X do centro do círculo.
 *
 * @param c O círculo de onde a coordenada X será lida. A função não modifica este objeto.
 * @return A coordenada X (em unidades de posição) do centro do círculo.
 */
 float circulo_get_x(const Circulo c);

/**
 * Obtém a coordenada Y do centro do círculo.
 *
 * @param c O círculo de onde a coordenada Y será lida. A função não modifica este objeto.
 * @return A coordenada Y (em unidades de posição) do centro do círculo.
 */
 float circulo_get_y(const Circulo c);

/**
 * Obtém o raio do círculo.
 *
 * @param c O círculo de onde o raio será lido. A função não modifica este objeto.
 * @return O raio do círculo (em unidades de comprimento).
 */
 double circulo_get_raio(const Circulo c);

/**
 * Calcula e retorna a área do círculo.
 *
 * @param c O círculo cuja área será calculada. A função não modifica este objeto.
 * @return A área do círculo (em unidades de área).
 */
 double circulo_get_area(const Circulo c);

/**
 * Obtém a cor da borda (stroke) do círculo.
 *
 * @param c O círculo de onde a cor da borda será lida. A função não modifica este objeto.
 * @return Ponteiro para uma string terminada em NUL que representa a cor da borda.
 *         Observação: dependendo da implementação, a string pode apontar para dados internos do objeto;
 *         não a libere nem a modifique.
 */
const char* circulo_get_corb(const Circulo c);

/**
 * Obtém a cor de preenchimento (fill) do círculo.
 *
 * @param c O círculo de onde a cor de preenchimento será lida. A função não modifica este objeto.
 * @return Ponteiro para uma string terminada em NUL que representa a cor de preenchimento.
 *         Observação: dependendo da implementação, a string pode apontar para dados internos do objeto;
 *         não a libere nem a modifique.
 */
 const char* circulo_get_corp(const Circulo c);
 /*---------------------------------------------------*/



 /*-------FUNÇÕES SETTERS-----------------------------*/

/**
 * @brief Define a coordenada X do círculo.
 *
 * Ajusta a posição horizontal do objeto Circulo para o valor especificado.
 *
 * @param c Handle/ponteiro para o objeto Circulo a ser modificado.
 * @param x Nova coordenada X (unidades dependem do sistema de coordenadas da aplicação).
 *
 * @note O parâmetro c deve referenciar um objeto válido. Se c for NULL, o comportamento é indefinido.
 */
 void circulo_set_x(Circulo c, float x);
 
/**
 * @brief Define a coordenada Y do círculo.
 *
 * Ajusta a posição vertical do objeto Circulo para o valor especificado.
 *
 * @param c Handle/ponteiro para o objeto Circulo a ser modificado.
 * @param y Nova coordenada Y (unidades dependem do sistema de coordenadas da aplicação).
 *
 * @note O parâmetro c deve referenciar um objeto válido. Se c for NULL, o comportamento é indefinido.
 */
 void circulo_set_y(Circulo c, float y);
 
/**
 * @brief Define a cor de preenchimento do círculo.
 *
 * Atribui ao círculo a cor de preenchimento indicada pela string corp.
 *
 * @param c Handle/ponteiro para o objeto Circulo a ser modificado.
 * @param corp String C (null-terminated) que representa a cor de preenchimento
 *             (por exemplo, nomes como "red" ou formatos como "#RRGGBB"), conforme a convenção usada pela implementação.
 *
 * @note A string corp deve ser válida durante a chamada. A implementação pode copiar a string ou
 *       armazenar apenas uma referência — consulte a documentação específica da implementação para detalhes.
 *       Se c for NULL, o comportamento é indefinido.
 */
 void circulo_set_corp(Circulo c, const char* corp);
 
/**
 * @brief Define a cor da borda (stroke) do círculo.
 *
 * Atribui ao círculo a cor da borda indicada pela string corb.
 *
 * @param c Handle/ponteiro para o objeto Circulo a ser modificado.
 * @param corb String C (null-terminated) que representa a cor da borda
 *             (por exemplo, nomes como "black" ou formatos como "#RRGGBB"), conforme a convenção usada pela implementação.
 *
 * @note A string corb deve ser válida durante a chamada. A implementação pode copiar a string ou
 *       armazenar apenas uma referência — consulte a documentação específica da implementação para detalhes.
 *       Se c for NULL, o comportamento é indefinido.
 */
 void circulo_set_corb(Circulo c, const char* corb);

 /*----------------------------------------------------*/
#endif