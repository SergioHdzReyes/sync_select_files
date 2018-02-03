//
// Created by Sergio Hernández on 02/02/18.
//

#include <ncurses.h>

#ifndef SYNC_SELECT_FILES_WINDOW_UTILS_H
#define SYNC_SELECT_FILES_WINDOW_UTILS_H

#endif //SYNC_SELECT_FILES_WINDOW_UTILS_H

//  ESTRUCTURA PARA INFORMACION DE LOS BORDES
typedef struct _win_borders_struct {
    chtype  ls, rs, ts, bs,
            tl, tr, bl, br;
} WIN_BORDER;

//  ESTRUCTURA PARA INFORMACION DE LAS DIMENSIONES DE LA VENTANA
typedef struct _WIN_struct {
    int startx, starty;
    int height, width;
    WIN_BORDER border;
} WIN;