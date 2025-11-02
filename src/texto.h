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

/**
 * @brief Retorna o identificador do objeto Texto.
 *
 * Recupera o ID associado ao objeto Texto indicado por 't'.
 *
 * @param t Texto cujo identificador será obtido. Se 't' for inválido (por exemplo, NULL),
 *          o comportamento é indefinido.
 * @return inteiro representando o identificador do Texto.
 */
int texto_get_id(const Texto t);
 
/**
 * @brief Retorna a coordenada X do objeto Texto.
 *
 * Obtém a posição X (em coordenadas do sistema utilizado pela aplicação) do Texto 't'.
 *
 * @param t Texto a partir do qual a coordenada X será obtida. Se 't' for inválido,
 *          o comportamento é indefinido.
 * @return valor float correspondente à coordenada X.
 */
float texto_get_x(const Texto t);
 
/**
 * @brief Retorna a coordenada Y do objeto Texto.
 *
 * Obtém a posição Y (em coordenadas do sistema utilizado pela aplicação) do Texto 't'.
 *
 * @param t Texto a partir do qual a coordenada Y será obtida. Se 't' for inválido,
 *          o comportamento é indefinido.
 * @return valor float correspondente à coordenada Y.
 */
float texto_get_y(const Texto t);
 
/**
 * @brief Calcula ou retorna a área ocupada pelo Texto.
 *
 * Fornece a área (por exemplo, em unidades de pixels² ou unidades do sistema gráfico)
 * ocupada pelo Texto 't'. O cálculo pode depender da fonte, tamanho e conteúdo do texto.
 *
 * @param t Texto cujo valor de área será obtido. Se 't' for inválido, o comportamento é indefinido.
 * @return valor double representando a área ocupada pelo Texto.
 */
double texto_get_area(const Texto t);
 
/**
 * @brief Retorna a âncora (alinhamento/posicionamento) do Texto.
 *
 * Retorna um caractere que indica a âncora ou justificativa do texto em relação
 * às suas coordenadas (por exemplo, esquerda, centro, direita, superior, inferior).
 * Os valores concretos e seu significado dependem da implementação.
 *
 * @param t Texto cujo atributo de âncora será obtido. Se 't' for inválido,
 *          o comportamento é indefinido.
 * @return caractere representando a âncora do Texto.
 */
char texto_get_ancora(const Texto t);
 
/**
 * @brief Retorna a cor da borda do Texto.
 *
 * Fornece uma string imutável que representa a cor da borda/contorno do Texto 't'
 * (por exemplo, "#RRGGBB" ou nome de cor). A string retornada é propriedade interna
 * do objeto Texto e não deve ser liberada pelo chamador.
 *
 * @param t Texto cujo atributo de cor de borda será obtido. Se 't' for inválido,
 *          o comportamento é indefinido.
 * @return ponteiro para string constante contendo a cor da borda. Pode ser NULL se não definida.
 */
const char *texto_get_corb(const Texto t);
 
/**
 * @brief Retorna a cor de preenchimento do Texto.
 *
 * Fornece uma string imutável que representa a cor de preenchimento (cor interna)
 * do Texto 't' (por exemplo, "#RRGGBB" ou nome de cor). A string retornada é
 * propriedade interna do objeto Texto e não deve ser liberada pelo chamador.
 *
 * @param t Texto cujo atributo de cor de preenchimento será obtido. Se 't' for inválido,
 *          o comportamento é indefinido.
 * @return ponteiro para string constante contendo a cor de preenchimento. Pode ser NULL se não definida.
 */
const char *texto_get_corp(const Texto t);
 
/**
 * @brief Retorna o conteúdo textual do objeto Texto.
 *
 * Retorna uma string imutável contendo o conteúdo (texto) associado ao objeto 't'.
 * A string é gerenciada internamente pelo objeto Texto; o chamador não deve tentar
 * modificá-la nem liberá-la. Para alterar o conteúdo, utilize a função apropriada
 * do módulo que manipula Texto.
 *
 * @param t Texto cujo conteúdo será retornado. Se 't' for inválido,
 *          o comportamento é indefinido.
 * @return ponteiro para string constante com o conteúdo do Texto. Pode ser NULL se vazio.
 */
const char *texto_get_conteudo(const Texto t);

/**
 * @brief Define a coordenada X do objeto Texto.
 *
 * Atualiza a posição horizontal (eixo X) do objeto Texto para o valor especificado.
 *
 * @param t Instância do Texto a ser modificada. Deve ser não NULL.
 * @param x Nova posição no eixo X (unidades dependem do contexto da aplicação).
 *
 * @pre t deve apontar para um objeto Texto válido.
 * @post A coordenada X do Texto será atualizada para o valor fornecido.
 */
void texto_set_x(Texto t, float x);
 
/**
 * @brief Define a coordenada Y do objeto Texto.
 *
 * Atualiza a posição vertical (eixo Y) do objeto Texto para o valor especificado.
 *
 * @param t Instância do Texto a ser modificada. Deve ser não NULL.
 * @param y Nova posição no eixo Y (unidades dependem do contexto da aplicação).
 *
 * @pre t deve apontar para um objeto Texto válido.
 * @post A coordenada Y do Texto será atualizada para o valor fornecido.
 */
void texto_set_y(Texto t, float y);
 
/**
 * @brief Define a cor de preenchimento (cor principal) do Texto.
 *
 * Associa ao objeto Texto a cor de preenchimento fornecida. O formato esperado da
 * string (por exemplo "#RRGGBB", nome da cor, etc.) depende da implementação.
 *
 * @param t Instância do Texto a ser modificada. Deve ser não NULL.
 * @param corp String representando a cor de preenchimento. Deve ser não NULL.
 *
 * @pre t e corp devem ser válidos e não NULL.
 * @post A cor de preenchimento do Texto será atualizada para a representação fornecida.
 */
void texto_set_corp(Texto t, const char* corp);
 
/**
 * @brief Define a cor da borda do Texto.
 *
 * Associa ao objeto Texto a cor da borda (stroke) fornecida. O formato da string
 * (por exemplo "#RRGGBB", nome da cor, etc.) depende da implementação.
 *
 * @param t Instância do Texto a ser modificada. Deve ser não NULL.
 * @param corb String representando a cor da borda. Deve ser não NULL.
 *
 * @pre t e corb devem ser válidos e não NULL.
 * @post A cor da borda do Texto será atualizada para a representação fornecida.
 */
void texto_set_corb(Texto t, const char* corb);
 
/**
 * @brief Define o conteúdo textual do objeto Texto.
 *
 * Atualiza o texto exibido/armazenado pelo objeto Texto para a string fornecida.
 *
 * @param t Instância do Texto a ser modificada. Deve ser não NULL.
 * @param conteudo String com o novo conteúdo textual. Deve ser não NULL.
 *
 * @pre t e conteudo devem ser válidos e não NULL.
 * @post O conteúdo do Texto será substituído pela string fornecida.
 */
void texto_set_conteudo(Texto t, const char* conteudo);

#endif