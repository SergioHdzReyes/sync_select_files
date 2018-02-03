// Created by Sergio Hernández on 18/01/18.

#include "shr/window_utils.h"
#include "shr/general_utils.h"
#include <form.h>

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