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
Texto criar_texto(float x, float y, const char* cor, const char* conteudo, int id);

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
void liberar_texto(Texto t);

#endif // TEXTO_H