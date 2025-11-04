#ifndef ESTILO_TEXTO_H
#define ESTILO_TEXTO_H

/**
 * @typedef EstiloTexto
 * @brief define um tipo opaco 'EstiloTexto' usando um ponteiro void.
 */
typedef void *EstiloTexto;

/**
 * @brief função que aloca e inicializa uma nova instância de EstiloTexto.
 *
 * @param 'familia_fonte' será a string que define a família da fonte (ex: "sans-serif").
 * @param 'peso_fonte' será o caractere que representa o peso da fonte (ex: 'n' para normal).
 * @param 'tamanho_fonte' será o valor inteiro para o tamanho da fonte.
 * @return retorna um ponteiro para a nova instância de EstiloTexto ou NULL em caso de falha.
 */
EstiloTexto estilo_texto_criar(const char *familia_fonte, char peso_fonte, int tamanho_fonte);

/**
 * @brief função que libera todos os recursos associados a uma instância de EstiloTexto.
 *
 * @param 'estilo' será o objeto EstiloTexto a ser destruído.
 */
void estilo_texto_destruir(EstiloTexto estilo);

/**
 * @brief função que consulta a família da fonte de um EstiloTexto.
 *
 * @param 'estilo' será o objeto EstiloTexto a ser consultado.
 * @return retorna uma string constante com o nome da família da fonte.
 */
const char *estilo_texto_obter_familia(EstiloTexto estilo);

/**
 * @brief função que consulta o peso da fonte de um EstiloTexto.
 *
 * @param 'estilo' será o objeto EstiloTexto a ser consultado.
 * @return retorna o caractere que representa o peso da fonte.
 */
char estilo_texto_obter_peso(EstiloTexto estilo);

/**
 * @brief função que consulta o tamanho da fonte de um EstiloTexto.
 *
 * @param 'estilo' será o objeto EstiloTexto a ser consultado.
 * @return retorna o valor inteiro correspondente ao tamanho da fonte.
 */
int estilo_texto_obter_tamanho(EstiloTexto estilo);

#endif // ESTILO_TEXTO_H