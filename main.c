//
// Created by Sergio Hernández on 18/01/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <form.h>

int main() {
    FILE *pf;
    //FIELD *fields[3];
    char path[1035];
    FORM *my_form;
    int ch;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    pf = popen("git status -s | cut -c4-", "r");

    if (pf == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    int row_increment = 4;
    int count_files = 0;
    while (fgets(path, sizeof(path) - 1, pf) != NULL) {
        mvprintw(row_increment, 20, path);
        row_increment += 2;
        count_files++;
    }
    refresh();

    FIELD *fields[count_files];
    for (int i = 1; i < (count_files - 1); i++) {
        fields[i - 1] = new_field(i, i, i, 1, 0, 0);

        /* Set field options */
        set_field_back(fields[i - 1], A_UNDERLINE);
        field_opts_off(fields[i - 1], O_AUTOSKIP);
    }
    fields[count_files - 1] = NULL;

    /* Create the form and post it */
    my_form = new_form(fields);
    post_form(my_form);
    refresh();

    /* Loop through to get user requests */
    while ((ch = getch()) != KEY_F(4)) {
        switch (ch) {
            case KEY_DOWN:
                /* Go to next field */
                form_driver(my_form, REQ_NEXT_FIELD);
                /* Go to the end of the present buffer */
                /* Leaves nicely at the last character */
                form_driver(my_form, REQ_END_LINE);
                break;
            case KEY_UP:
                /* Go to previous field */
                form_driver(my_form, REQ_PREV_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;
            default:
                /* If this is a normal character, it gets */
                /* Printed				  */
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