#ifndef COMPLEMENTAR_H
#define COMPLEMENTAR_H

/**
 * @brief função que calcula a cor complementar (inversa) de uma cor fornecida. 
 *
 * @param 'cor_original' será a string (constante) da cor original.
 * @return retorna um ponteiro para uma string estática (buffer interno) contendo o 
 * hex da cor complementar (ex: "#00FFFF"). 
 */
const char* cor_get_complementar(const char* cor_original);

#endif // COMPLEMENTAR_H