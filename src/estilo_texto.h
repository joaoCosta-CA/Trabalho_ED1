#ifndef ESTILO_TEXTO_H
#define ESTILO_TEXTO_H

/**
 * @typedef EstiloTexto
 * @brief Ponteiro opaco que representa uma instância do estilo de texto.
 */
typedef void *EstiloTexto;

/**
 * @brief Aloca e inicializa uma nova instância de EstiloTexto.
 *
 * Esta função cria um objeto para armazenar as características de um estilo
 * de texto com base nos parâmetros fornecidos.
 *
 * @param familia_fonte Uma string que define a família da fonte (ex: "sans-serif").
 * @param peso_fonte Um caractere que representa o peso da fonte (ex: 'n' para normal).
 * @param tamanho_fonte Um valor inteiro para o tamanho da fonte.
 * @return Um ponteiro para a nova instância de EstiloTexto ou NULL em caso de falha.
 */
EstiloTexto estilo_texto_criar(const char *familia_fonte, char peso_fonte, int tamanho_fonte);

/**
 * @brief Libera todos os recursos associados a uma instância de EstiloTexto.
 *
 * Garante que a memória alocada para o objeto de estilo de texto seja
 * completamente desalocada, prevenindo vazamentos de memória.
 *
 * @param estilo O objeto EstiloTexto a ser destruído.
 */
void estilo_texto_destruir(EstiloTexto estilo);

/**
 * @brief Consulta a família da fonte de um EstiloTexto.
 *
 * @param estilo O objeto EstiloTexto a ser consultado.
 * @return Uma string constante com o nome da família da fonte.
 * (Atenção: não modifique ou libere este ponteiro).
 */
const char *estilo_texto_obter_familia(EstiloTexto estilo);

/**
 * @brief Consulta o peso da fonte de um EstiloTexto.
 *
 * @param estilo O objeto EstiloTexto a ser consultado.
 * @return O caractere que representa o peso da fonte.
 */
char estilo_texto_obter_peso(EstiloTexto estilo);

/**
 * @brief Consulta o tamanho da fonte de um EstiloTexto.
 *
 * @param estilo O objeto EstiloTexto a ser consultado.
 * @return O valor inteiro correspondente ao tamanho da fonte.
 */
int estilo_texto_obter_tamanho(EstiloTexto estilo);

#endif // ESTILO_TEXTO_H