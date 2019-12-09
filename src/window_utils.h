//
// Created by Sergio Hernández on 02/02/18.
//

#include <ncurses.h>
#include <stdbool.h>

#ifndef SYNC_SELECT_FILES_WINDOW_UTILS_H
#define SYNC_SELECT_FILES_WINDOW_UTILS_H

/**
 * Estructura para informacion de los bordes de la ventana
 */
typedef struct _win_borders_struct {
    chtype  ls, rs, ts, bs,
            tl, tr, bl, br;
} WIN_BORDER;

/**
 * Estructura para informacion de las dimensiones de la ventana
 */
typedef struct _WIN_struct {
    int startx, starty;
    int height, width;
    WIN_BORDER border;
} WIN;

/**
 * Se inicializan caracteres para el marco de la pantalla
 *
 * @param window Estructura de datos de la ventana
 * @return void
 */
void init_win_params(WIN *window);

/**
 * Se crea marco de ventana con opcion a limpiar pantalla
 *
 * @param window Estructura de datos de la ventana
 * @param clear True o False para limpiar la pantalla
 * @return void
 */
void create_box(WIN *window, bool clear);

#endif //SYNC_SELECT_FILES_WINDOW_UTILS_H
