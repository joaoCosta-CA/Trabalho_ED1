#include "lib/argumentos/argumentos.h"
#include "lib/ler_arq/leitor.h"
#include "lib/leitor_geo/leitor_geo.h"
#include "lib/leitor_qry/leitor_qry.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc < 5) {
        printf("Uso: ./ted [-e <dir_base>] -f <arq.geo>  [-q <arq.qry>]  -o ./output\n");
        return 1;
    }

    const char *output_path = get_option_value(argc, argv, "o");
    const char *geo_input_path = get_option_value(argc, argv, "f");
    const char *qry_input_path = get_option_value(argc, argv, "q");
    const char *command_suffix = get_command_suffix(argc, argv); 

    if (geo_input_path == NULL || output_path == NULL) {
        printf("Erro: Os parâmetros -f e -o são obrigatórios.\n");
        exit(EXIT_FAILURE);
    }

    // --- Leitura e Processamento do Arquivo .geo ---
    DadosArquivo geo_file = dados_arquivo_criar(geo_input_path);
    if (geo_file == NULL) {
        printf("Erro: Falha ao abrir ou ler o arquivo de entrada '%s'\n", geo_input_path);
        exit(EXIT_FAILURE);
    }
    
    Chao ground = processar_arquivo_geo(geo_file, output_path, NULL);

    if (qry_input_path != NULL) {
        DadosArquivo qry_file = dados_arquivo_criar(qry_input_path);
        if (qry_file == NULL) {
            printf("Erro: Falha ao abrir ou ler o arquivo de consulta '%s'\n", qry_input_path);
            // Limpa a memória alocada antes de sair
            destruir_formas_geo(ground);
            dados_arquivo_destruir(geo_file);
            exit(EXIT_FAILURE);
        }

        processar_arquivo_qry(ground, qry_file, geo_file, output_path);

        dados_arquivo_destruir(qry_file);
    }
    dados_arquivo_destruir(geo_file);
    destruir_formas_geo(ground);

    printf("Processamento concluído com sucesso.\n");
    return 0;
}