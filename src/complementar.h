#ifndef COMPLEMENTAR_H
#define COMPLEMENTAR_H

/**
 * @brief Calcula a cor complementar (inversa) de uma cor fornecida.
 *
 * Aceita nomes de cores (ex: "red") ou formatos hex (ex: "#FF0000" ou "#F00").
 * Se a cor não for reconhecida, trata como preto ("#000000").
 *
 * @param cor_original A string (constante) da cor original.
 * @return Um ponteiro para uma string estática (buffer interno) contendo o 
 * hex da cor complementar (ex: "#00FFFF"). 
 * @warning O buffer retornado é estático e será sobrescrito na próxima
 * chamada a esta função.
 */
const char* cor_get_complementar(const char* cor_original);

#endif // COMPLEMENTAR_H