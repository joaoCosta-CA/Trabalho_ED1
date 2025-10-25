#ifndef TEXTO_H
#define TEXTO_H

/**
 * @brief Define um tipo opaco 'Texto' usando um ponteiro void.
 * A estrutura interna é mantida oculta no arquivo .c, e os usuários
 * da biblioteca interagem apenas com este ponteiro.
 */
typedef void *Texto;

/**
 * @brief Cria uma nova instância de um objeto de texto.
 *
 * @param id Um identificador numérico para o texto.
 * @param x A coordenada X da âncora do texto.
 * @param y A coordenada Y da âncora do texto.
 * @param cor A string que representa a cor do texto (ex: "#00FF00").
 * @param conteudo A string de conteúdo a ser exibida.
 * @return Um ponteiro opaco 'Texto' (void*) para o objeto criado,
 * ou NULL se a alocação de memória falhar.
 */
Texto criar_texto(int id, float x, float y, const char* corb, const char* corp, char ancora, const char* conteudo);

/**
 * @brief Calcula e retorna a "área" ocupada pelo texto.
 * A área é definida como: 20.0 * (número de caracteres no conteúdo).
 *
 * @param t O ponteiro opaco 'Texto' para o qual a área será calculada.
 * @return O valor da área calculada como um float. Retorna 0.0 se o ponteiro for nulo.
 */
float area_texto(const Texto t);

/**
 * @brief Libera toda a memória alocada para um objeto de texto.
 *
 * @param t O ponteiro opaco 'Texto' a ser liberado.
 */
void destruirTexto(Texto t);


/*---------------FUNÇÕES GETTERS-------------------*/
int texto_get_id(const Texto t);
float texto_get_x(const Texto t);
float texto_get_y(const Texto t);
double texto_get_area(const Texto t);
char texto_get_ancora(const Texto t);
const char *texto_get_corb(const Texto t);
const char *texto_get_corp(const Texto t);
const char *texto_get_conteudo(const Texto t);

/*---------------FUNÇÕES SETTERS-------------------*/
void texto_set_x(Texto t, float x);
void texto_set_y(Texto t, float y);
void texto_set_corp(Texto t, const char* corp);
void texto_set_corb(Texto t, const char* corb);
void texto_set_conteudo(Texto t, const char* conteudo);


#endif