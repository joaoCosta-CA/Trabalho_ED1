// Arquivo: leitor_qry.h
#ifndef LEITOR_QRY_H
#define LEITOR_QRY_H

#include "leitor_geo.h"
#include "leitor.h"

/**
 * @brief função que processa um arquivo de consulta .qry, manipulando as formas e
 * elementos de jogo carregados a partir do arquivo .geo.
 * @param 'chao' será a estrutura contendo as formas geométricas lidas do .geo.
 * @param 'dados_qry' será as informações sobre o arquivo .qry a ser lido.
 * @param 'dados_geo' será as informações sobre o arquivo .geo original (usado para nomes de saída).
 * @param 'caminho_saida' será o diretório onde os arquivos .svg e .txt de saída serão salvos.
 */
void processar_arquivo_qry(Chao chao, DadosArquivo dados_qry, DadosArquivo dados_geo, const char* caminho_saida);

#endif