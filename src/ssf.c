#include "ssf.h"
#include "ssf_app.h"

int main( int argc, char *argv[] ) {
    DIR *dir = opendir(".git");

    if (!dir) {
        printf("No se encontro un proyecto Git en el directorio actual\n");
        return 1;
    }
    closedir(dir);

    g_resources_register(ssf_get_resource());

    return g_application_run(G_APPLICATION(ssf_app_new()), argc, argv);
}