// Created by Sergio Hernández on 18/01/18.

#include "shr/window_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <form.h>
#include <sys/stat.h>

//  DEFINICION DE FUNCIONES
void init_win_params(WIN *window);
void create_box(WIN *window, bool clear);
void add_array_element(char **, int *);

int main() {
    FILE *pf;
    //FIELD *fields[3];
    WIN window;
    char path[1035];
    FORM *my_form;
    int ch;
    //  SE GUARDARAN LOS NOMBRES DE LOS ARCHIVOS
    int array_index = 1;
    int *pointer_index = &array_index;
    char** array = malloc(array_index * sizeof(*array));
    add_array_element(array, pointer_index);
    array[0] = "Prueba";

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    //  SE INICIALIZA LA VENTANA
    init_win_params(&window);
    create_box(&window, false);

    pf = popen("git status -s | cut -c4-", "r");

    if (pf == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    int row_increment = 4;
    int count_files = 0;

    //  SE PINTAN LOS NOMBRES DE LOS ARCHIVOS MODIFICADOS
    while (fgets(path, sizeof(path) - 1, pf) != NULL) {

        mvprintw(row_increment, 15, "[ ]");
        mvprintw(row_increment, 20, path);
        row_increment += 1;
        count_files++;
    }
    char test[100];
    sprintf(test, "************************ Se modificaron en total %d archivos ************************", COLS);
    mvprintw(1, 40, test);
    refresh();
    mvprintw(2, 10, "INDEX_: %d, Valor 1: %s", array_index, array[0]);
    refresh();

    //  Se pintan los fields
    FIELD *fields[count_files];
    for (int i = 1; i <= count_files; i++) {
        //fields[i - 1] = new_field(i, 1, i, 50, 0, 0);

        /* Set field options */
        //set_field_back(fields[i - 1], A_UNDERLINE);
        //field_opts_off(fields[i - 1], O_AUTOSKIP);
    }
    fields[count_files] = NULL;

    //  Se añade el formulario
    my_form = new_form(fields);
    post_form(my_form);
    refresh();

    //mvprintw(4, 10, "Value 1:");

    //  SE EJECUTA EL CICLO PARA RECIBIR LA PETICION DE USUARIO
    while ((ch = getch()) != KEY_F(4)) {
        switch (ch) {
            case KEY_DOWN:
                //  IR A SIGUIENTE CAMPO
                form_driver(my_form, REQ_NEXT_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;
            case KEY_UP:
                //  IR A CAMPO ANTERIOR
                form_driver(my_form, REQ_PREV_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;
            default:
                //  SI ES UN CARACTER NORMAL LO IMPRIME
                form_driver(my_form, ch);
                break;
        }
    }

    if (pclose(pf) != 0)
        fprintf(stderr, "Error: Failed to close command stream \n");

    unpost_form(my_form);
    free_form(my_form);
    free_field(fields[0]);
    free_field(fields[1]);

    endwin();
    return 0;
}

void add_array_element(char **array, int *index)
{
    (*index)++;
    array = realloc(array, (*index) * sizeof(array));
}

//  VERIFICA SI ES UN ARCHIVO REGULAR O UN DIRECTORIO
int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);

    return S_ISREG(path_stat.st_mode);
}

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