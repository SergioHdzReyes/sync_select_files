//
// Created by Sergio Hernández on 02/02/18.
//

#include <ncurses.h>

#ifndef SYNC_SELECT_FILES_WINDOW_UTILS_H
#define SYNC_SELECT_FILES_WINDOW_UTILS_H

#endif //SYNC_SELECT_FILES_WINDOW_UTILS_H

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
void init_win_params(WIN *window)
{
    window->height = LINES;
    window->width = COLS;
    window->startx = 0;
    window->starty = 0;

    window->border.ls = '|';
    window->border.rs = '|';
    window->border.ts = '-';
    window->border.bs = '-';

    window->border.tl = '+';
    window->border.tr = '+';
    window->border.bl = '+';
    window->border.br = '+';
}

/**
 * Se crea marco de ventana con opcion a limpiar pantalla
 *
 * @param window Estructura de datos de la ventana
 * @param clear True o False para limpiar la pantalla
 * @return void
 */
void create_box(WIN *window, bool clear)
{
    int i, j;
    int x, y, w, h;

    x = window->startx;
    y = window->starty;
    w = window->width;
    h = window->height;

    if (clear == FALSE) {
        mvaddch(y, x, window->border.tl);           //  ESQUINA TOP-LEFT
        mvaddch(y, x + w - 1, window->border.tr);       //  ESQUINA TOP-RIGHT
        mvaddch(y + h - 1, x, window->border.bl);       //  ESQUINA BOTTOM-LEFT
        mvaddch(y + h - 1, x + w - 1, window->border.br);   //  ESQUINA BOTTOM-RIGHT

        mvhline(y, x + 1, window->border.ts, w - 2);        //  LINEA HORIZONTAL-TOP
        mvhline(y + h - 1, x + 1, window->border.bs, w - 2);//  LINEA HORIZONTAL-BOTTOM
        mvvline(y + 1, x, window->border.ls, h - 2);        //  LINEA VERTICAL-LEFT
        mvvline(y + 1, x + w - 1, window->border.rs, h - 2);//  LINEA VERTICAL-RIGHT
    } else {
        for (j = y; j <= (y + h); j++) {
            for (i = x; i <= (x + w); i++)
                mvaddch(j, i, ' ');
        }
    }

    refresh();
}