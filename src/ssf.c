#include "ssf.h"
#include "ssf_app.h"
#include "libssfservers.h"

int main( int argc, char *argv[] ) {
    DIR *dir = opendir(".git");
    config_t cfg;

    // Version control system validation
    if (!dir) {
        printf("No se encontro un proyecto Git en el directorio actual\n");
        return 1;
    }
    closedir(dir);

    // Servers management validation
    config_init(&cfg);
    if (srvs_check_empty_list(&cfg)) {
        printf("No se encontro servidor disponible, favor de agregar...\n");
        return 1;
    }
    config_destroy(&cfg);

    // Start user interface
    g_resources_register(ssf_get_resource());

    return g_application_run(G_APPLICATION(ssf_app_new()), argc, argv);
}