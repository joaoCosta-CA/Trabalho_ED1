#ifndef LEITOR_GEO_H
#define LEITOR_GEO_H
#include "../ler_arq/leitor.h"
#include "../fila/fila.h"
#include "../formas/formas.h"
#include <stdio.h>

/**
 * @typedef Chao
 * @brief Ponteiro opaco que representa a coleção de formas geométricas no ambiente do jogo.
 *
 * Funciona como um "handle" para a estrutura de dados que armazena todas as formas
 * criadas a partir do arquivo .geo, ocultando os detalhes da implementação.
 */
typedef void *Chao;

typedef void* FormaGeometrica;

/**
 * @brief Executa os comandos de um arquivo .geo e instancia as formas geométricas.
 *
 * Esta função itera sobre as linhas de comando fornecidas, interpreta cada uma,
 * aloca a memória para a forma geométrica descrita e a armazena na estrutura "Chao".
 *
 * @param dados_arquivo A estrutura contendo as linhas do arquivo .geo a serem processadas.
 * @param caminho_saida O diretório base onde os arquivos de saída (como .svg) serão gerados.
 * @param sufixo_comando Um sufixo opcional a ser adicionado ao nome dos arquivos de saída.
 * @return Um ponteiro do tipo Chao para a coleção de formas criadas, ou NULL em caso de erro.
 */
Chao processar_arquivo_geo(DadosArquivo dados_arquivo, const char *caminho_saida,const char *sufixo_comando);

/**
 * @brief Libera toda a memória associada ao "Chao" e às formas que ele contém.
 *
 * Essencial para a prevenção de vazamentos de memória, esta função deve ser chamada
 * ao final da execução para desalocar todos os recursos criados por `processar_arquivo_geo`.
 *
 * @param chao O ponteiro para a estrutura Chao que deve ser destruída.
 */
void destruir_formas_geo(Chao chao);

/**
 * @brief Retorna a fila principal de formas que estão no "chão".
 * Esta função concede acesso à fila para que outros módulos possam
 * remover formas dela (ex: comando 'lc').
 * @param chao O ponteiro opaco para o estado do leitor_geo.
 * @return A FILA contendo as formas geométricas.
 */
FILA leitor_geo_get_fila_principal(Chao chao);

/**
 * @brief Obtém o tipo de uma forma geométrica (Círculo, Retângulo, etc.).
 * @param forma O ponteiro opaco para a forma.
 * @return O tipo da forma, conforme o enum ShapeType.
 */
ShapeType forma_get_tipo(FormaGeometrica forma);


/**
 * @brief Obtém o ponteiro para os dados específicos da forma (ex: a struct do Círculo).
 * @param forma O ponteiro opaco para a forma.
 * @return Um ponteiro void* para os dados específicos da forma.
 */
void* forma_get_dados(FormaGeometrica forma);

/**
 * @brief Abre um arquivo SVG no caminho especificado e escreve o cabeçalho.
 * @param caminho_completo O caminho completo do arquivo .svg a ser criado.
 * @return Um ponteiro para o arquivo (FILE*) aberto, ou NULL em caso de erro.
 */
FILE* svg_iniciar(const char* caminho_completo);

/**
 * @brief Desenha todas as formas contidas no "Chao" em um arquivo SVG já aberto.
 * @param arquivo_svg O ponteiro do arquivo retornado por svg_iniciar.
 * @param chao O estado do "chão" contendo as formas a serem desenhadas.
 */
void svg_desenhar_chao(FILE* arquivo_svg, Chao chao);

/**
 * @brief Escreve a tag de fechamento do SVG e fecha o arquivo.
 * @param arquivo_svg O ponteiro do arquivo a ser finalizado.
 */
void svg_finalizar(FILE* arquivo_svg);

/**
 * @brief Obtém o identificador associado a uma forma geométrica.
 *
 * Retorna o ID que identifica a forma passada como argumento. O ID é
 * normalmente usado para referenciação e busca de propriedades específicas
 * da forma.
 *
 * @param forma Instância (ou ponteiro) da forma geométrica cujo ID será
 *              obtido.
 * @return int Valor do identificador da forma. Em caso de forma inválida
 *             (por exemplo, NULL ou estrutura sem ID definido) a função
 *             retorna um valor indicativo de erro (por exemplo, -1).
 * 
 * @pre  'forma' deve representar uma forma válida; caso contrário o valor
 *       de retorno indica erro.
 */
int forma_get_id(FormaGeometrica forma);

/**
 * @brief Libera todos os recursos associados a uma forma geométrica.
 *
 * Esta função deve desalocar toda a memória e recursos internos usados pela
 * forma (dados geométricos, strings, listas internas, etc.), garantindo que
 * não haja vazamento de memória.
 *
 * @param forma Instância (ou ponteiro) da forma geométrica a ser destruída.
 *
 * @note Após a chamada, qualquer acesso a 'forma' é indefinido.
 * @note Se 'forma' for NULL, a função não realiza nenhuma ação.
 * @post  Recursos associados à forma foram liberados e não devem ser usados
 *        novamente.
 */
void destruir_forma_completa(FormaGeometrica forma);


/**
 * @brief Retorna a coordenada X da forma geométrica.
 *
 * Obtém a coordenada X do ponto de referência da FormaGeometrica fornecida.
 * A função não altera o estado da estrutura passada como argumento.
 *
 * @param forma Estrutura FormaGeometrica devidamente inicializada.
 * @return Coordenada X da forma (valor em double).
 */
double forma_get_x(FormaGeometrica forma);

/**
 * @brief Retorna a coordenada Y da forma geométrica.
 *
 * Obtém a coordenada Y do ponto de referência da FormaGeometrica fornecida.
 * A função não altera o estado da estrutura passada como argumento.
 *
 * @param forma Estrutura FormaGeometrica devidamente inicializada.
 * @return Coordenada Y da forma (valor em double).
 */
double forma_get_y(FormaGeometrica forma);


/**
 * Retorna a cor de preenchimento da forma.
 *
 * @param forma    Instância válida de FormaGeometrica (não-NULL).
 *
 * @return Ponteiro para uma string NUL-terminada que representa a cor de preenchimento
 *         (por exemplo nome ou código da cor). O ponteiro aponta para memória gerida
 *         internamente pela forma; o chamador NÃO deve modificar nem liberar essa string.
 *         A validade do ponteiro está vinculada ao ciclo de vida da forma e pode ser
 *         alterada por operações que modifiquem a forma.
 *
 * @note Se 'forma' for NULL, o comportamento é indefinido (ou a função poderá retornar NULL,
 *       conforme a implementação). Esta função não é necessariamente thread-safe; sincronize
 *       acessos concorrentes externamente.
 */
const char* forma_get_cor_preenchimento(FormaGeometrica forma);

/**
 * Retorna a cor da borda da forma.
 *
 * @param forma    Instância válida de FormaGeometrica (não-NULL).
 *
 * @return Ponteiro para uma string NUL-terminada que representa a cor da borda.
 *         O ponteiro aponta para memória interna da forma; o chamador NÃO deve
 *         modificar nem liberar essa string. A validade do ponteiro depende do
 *         ciclo de vida e do estado da forma.
 *
 * @note Se 'forma' for NULL, o comportamento é indefinido (ou a função poderá retornar NULL,
 *       conforme a implementação). Esta função não é necessariamente thread-safe; sincronize
 *       acessos concorrentes externamente.
 */
const char* forma_get_cor_borda(FormaGeometrica forma);

/**
 * Define a cor da borda da forma.
 *
 * @param forma     Instância válida de FormaGeometrica (não-NULL).
 * @param nova_cor  String NUL-terminada com o nome ou código da nova cor (deve ser não-NULL).
 *
 * @behavior A função atualiza a cor da borda da forma para o valor fornecido.
 *           Implementações devem copiar o conteúdo de 'nova_cor' para armazenamento
 *           interno ou documentar claramente a política de ownership; após a chamada,
 *           o chamador pode modificar ou liberar a string passada.
 *
 * @effects Substitui a cor de borda anterior pela nova. Em caso de falha (por exemplo,
 *          falha de alocação), o estado da forma deverá permanecer inalterado.
 *
 * @note 'forma' e 'nova_cor' devem ser válidos; passar NULL resulta em comportamento
 *       indefinido, salvo indicação contrária na implementação. A operação não é
 *       necessariamente thread-safe; proteja acessos concorrentes externamente.
 */
void forma_set_cor_borda(FormaGeometrica forma, const char* nova_cor);


/**
 * @brief Cria uma cópia (clone) de uma FormaGeometrica.
 *
 * Esta função realiza uma cópia profunda da forma fornecida, duplicando
 * quaisquer recursos internos necessários (por exemplo, buffers, listas,
 * cadeias de caracteres) para que o clone seja independente da forma original.
 *
 * @param forma_original
 *     A FormaGeometrica a ser clonada. A forma original não é modificada.
 *
 * @param proximo_id
 *     Ponteiro para um inteiro usado para atribuir um novo identificador ao
 *     clone. Se proximo_id for != NULL, o clone recebe como id o valor
 *     apontado por proximo_id e o inteiro apontado é incrementado
 *     (*proximo_id)++ para preparar o próximo id disponível. Se proximo_id
 *     for NULL, o clone preserva o id da forma_original.
 *
 * @return
 *     Uma nova FormaGeometrica contendo a cópia profunda da forma_original.
 *     O chamador é responsável por liberar quaisquer recursos alocados pelo
 *     clone usando a função apropriada do módulo (por exemplo, uma função
 *     de destruição/liberação de forma).
 *
 * @note
 *     - Em caso de falha de alocação, o comportamento depende da implementação
 *       concreta; recomenda-se verificar/validar o objeto retornado conforme as
 *       convenções do projeto (por exemplo, um id inválido ou um campo interno
 *       NULL).  
 *     - A função faz uma cópia completa; modificações no clone não afetam a
 *       forma_original e vice-versa.
 */
FormaGeometrica forma_clonar(FormaGeometrica forma_original, int* proximo_id);


/**
 * @brief Retorna o maior identificador (ID) entre as formas presentes no Chao.
 *
 * Percorre a fila principal de formas contida em 'chao' e retorna o maior ID
 * atualmente em uso. Útil para atribuição de novos IDs ou para consultas de
 * consistência.
 *
 * @param chao Ponteiro opaco para o estado do leitor_geo.
 * @return O maior ID encontrado (valor >= 0). Retorna -1 se 'chao' for NULL ou
 *         se não houver formas registradas.
 */
int leitor_geo_get_max_id(Chao chao);

#endif