#include "window_utils.h"

struct _win_borders_struct;

struct _WIN_struct;

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
