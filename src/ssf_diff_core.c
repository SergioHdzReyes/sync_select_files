//
// Created by sergio on 07/05/23.
//

#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ssf_diff_core.h"

char operation[500][100];
char filepath[500][100];

short int diff_count;

int ssf_diff_start() {
    if (process_command()) {
        return 1;
    } else {
        return 0;
    }
    int cont = 0;
    /*while (output[cont] != NULL) {
        printf("COUNT: %d, VAR: %s\n", cont, output[cont]);
        cont++;
    }*/
}

void ssf_diff_end() {

}

int process_command() {
    FILE *fp;
    char path[1035];
    char cmd[100];
    char *sync_cmd = "rsync -an --delete --out-format=\"%o %n\" --cvs-exclude . /opt/sync_select_files/";

    /* Open the command for reading. */
    sprintf(cmd, "%s", sync_cmd);
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    diff_count = 0;

    //output = malloc((500)*sizeof(char*));
    /*if ( output == NULL ) {
        printf("Error: out of memory.\n");
        return;
    }*/

    while (fgets(path, sizeof(path), fp) != NULL) {
        size_t char_count = (size_t) strlen(path);
        //output[count] = (char*) calloc(char_count, sizeof(char));

        /*if ( output[count] == NULL ) {
            printf("ERROR\n");
            break;
        }*/

        if (strcmp(&path[char_count-2], "/\n") == 0) {
            continue;
        }

        // Split string: "operation file"
        char *op, *filep;
        char *search = " ";
        op = strtok(path, search);
        filep = strtok(NULL, search);

        strcpy(operation[diff_count], op);
        strcpy(filepath[diff_count], filep);

        diff_count++;
    }

    pclose(fp);

    return 1;
}
