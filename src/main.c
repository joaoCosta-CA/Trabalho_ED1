#include "lib/ler_arq/leitor.h"
#include "lib/argumentos/argumentos.h"
#include "lib/leitor_geo/leitor_geo.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if (argc > 10) {
    printf("Erro: Muitos argumentos\n");
    exit(1);
  }

  const char *output_path = get_option_value(argc, argv, "o");
  const char *geo_input_path = get_option_value(argc, argv, "f");
//   const char *qry_input_path = get_option_value(argc, argv, "q");
  const char *command_suffix = get_command_suffix(argc, argv);

  if (geo_input_path == NULL || output_path == NULL) {
    printf("Error: -f e -o são necessários\n");
    exit(1);
  }typedef void *Chao;

  Chao processar_arquivo_geo(DadosArquivo fileData, const char *output_path,const char *command_suffix);

  void destruir_formas_geo(Chao ground);

  DadosArquivo geo_file = dados_arquivo_criar(geo_input_path);
  if (geo_file == NULL) {
    printf("Erro: Falha ao criar um Arquivo de Dados\n");
    exit(1);
  }// Declaration of the function that will be in the args_handler module

  Chao ground = processar_arquivo_geo(geo_file, output_path, command_suffix);

  dados_arquivo_destruir(geo_file);
  destruir_formas_geo(ground);

  return 0;
}