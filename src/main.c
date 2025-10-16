#include "lib/argumentos/argumentos.h"
#include "lib/ler_arq/leitor.h"
#include "lib/leitor_geo/leitor_geo.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    // Uma verificação do número mínimo de argumentos
    // Precisa de pelo menos 5: ./ted -f arquivo.geo -o caminho
    if (argc < 5) {
        printf("Uso: ./ted -f <arq.geo> -o <dir_saida> [-q <arq.qry>]\n");
        return 1;
    }

    // --- Processamento dos Argumentos ---
    const char *output_path = get_option_value(argc, argv, "o");
    const char *geo_input_path = get_option_value(argc, argv, "f");
    // const char *qry_input_path = get_option_value(argc, argv, "q"); // Para ser usado depois
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
    
    Chao ground = processar_arquivo_geo(geo_file, output_path, command_suffix);

    // --- Limpeza de Memória ---
    dados_arquivo_destruir(geo_file);
    destruir_formas_geo(ground);

    printf("Processamento concluído com sucesso.\n");
    return 0;
}