//
// Created by Sergio Hernández on 03/02/18.
//

#ifndef SYNC_SELECT_FILES_GENERAL_UTILS_H
#define SYNC_SELECT_FILES_GENERAL_UTILS_H

#include <stdlib.h>
#include <sys/stat.h>

/**
 * Añade un elemento mas al puntero array
 *
 * @param array Puntero al elemento array en memoria
 * @param index Indice para mantener el tamaño en memoria
 * @return void
 */
void add_array_element(char **array, int *index);

/**
 * Verifica si la ruta dada es un archivo o directorio.
 * El valor devuelto sera true para un archivo regular o false para un directorio.
 *
 * @param path Ruta a analizar
 * @return integer
 */
int is_regular_file(const char *path);

#endif //SYNC_SELECT_FILES_GENERAL_UTILS_H
