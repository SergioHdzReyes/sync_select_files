//
// Created by Sergio Hernández on 08/02/18.
//

#include <stdio.h>
#include "configure/configure_host.h"

int main(int argc, char **argv) {
    printf("Bienvenido a la configuracion de Sync Select.\n");
    printf("Selecciona una de las siguientes opciones:\n");
    printf("h - Para añadir un nuevo host a utilizar en la sincronizacion. \n");

    switch (getchar()) {
        case 'h':
            add_host();
            break;
        default:
            printf("No selecciono una opcion. \nAbortando...\n\n");
            return 0;
            break;
    }
}