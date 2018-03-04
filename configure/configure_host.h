//
// Created by Sergio Hernández on 08/02/18.
//

#include <memory.h>

#ifndef SYNC_SELECT_FILES_CONFIGURE_HOST_H
#define SYNC_SELECT_FILES_CONFIGURE_HOST_H

#endif //SYNC_SELECT_FILES_CONFIGURE_HOST_H

void add_host(){
    FILE *file_hosts;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    file_hosts = fopen("hosts", "a+");
    if (file_hosts == NULL)
        perror("Error al abrir el archivo.");

    printf("Inserte el host a guardar (quit para terminar):  ");
    while ((read = getline(&line, &len, stdin)) != -1) {
        if (strcmp(line, "\n") == 0)
            continue;
        if (strcmp(line, "quit\n") == 0)
            break;
        printf("Inserte el host a guardar (quit para terminar):  ");

        if (read > 0) {
            fputs(line, file_hosts);
        }
    }
    printf ("Finalizo configuracion!\n\n");

    fclose(file_hosts);
}