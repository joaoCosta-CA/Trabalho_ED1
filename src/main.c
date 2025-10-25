#include "lib/argumentos/argumentos.h"
#include "lib/ler_arq/leitor.h"
#include "lib/leitor_geo/leitor_geo.h"
#include "lib/leitor_qry/leitor_qry.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FULL_PATH 1024

int main(int argc, char *argv[])
{

    if (argc < 5)
    {
        printf("Uso: ./ted [-e <dir_base>] -f <arq.geo>  [-q <arq.qry>]  -o ./output\n");
        return 1;
    }

    const char *base_input_path = get_option_value(argc, argv, "e");
    const char *output_path = get_option_value(argc, argv, "o");
    const char *geo_input_path = get_option_value(argc, argv, "f");
    const char *qry_input_path = get_option_value(argc, argv, "q");

    if (geo_input_path == NULL || output_path == NULL)
    {
        printf("Erro: Os parâmetros -f e -o são obrigatórios.\n");
        exit(EXIT_FAILURE);
    }

    char geo_full_path[MAX_FULL_PATH];
    char qry_full_path[MAX_FULL_PATH];

    if (base_input_path != NULL)
    {

        snprintf(geo_full_path, MAX_FULL_PATH, "%s/%s", base_input_path, geo_input_path);
    }
    else
    {
        strncpy(geo_full_path, geo_input_path, MAX_FULL_PATH - 1);
        geo_full_path[MAX_FULL_PATH - 1] = '\0';
    }

    if (qry_input_path != NULL)
    {
        if (base_input_path != NULL)
        {
            snprintf(qry_full_path, MAX_FULL_PATH, "%s/%s", base_input_path, qry_input_path);
        }
        else
        {
            strncpy(qry_full_path, qry_input_path, MAX_FULL_PATH - 1);
            qry_full_path[MAX_FULL_PATH - 1] = '\0';
        }
    }

    // --- Leitura e Processamento do Arquivo .geo ---
    DadosArquivo geo_file = dados_arquivo_criar(geo_full_path);
    if (geo_file == NULL){
        printf("Erro: Falha ao abrir ou ler o arquivo de entrada '%s'\n", geo_full_path);
        exit(EXIT_FAILURE);
    }

    Chao ground = processar_arquivo_geo(geo_file, output_path, NULL);

    if (qry_input_path != NULL){
        DadosArquivo qry_file = dados_arquivo_criar(qry_full_path);
        if (qry_file == NULL){
            printf("Erro: Falha ao abrir ou ler o arquivo de consulta '%s'\n", qry_full_path);
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