#include "ssf.h"
#include "ssf_app.h"

int main( int argc, char *argv[] ) {
    g_resources_register(ssf_get_resource());

    return g_application_run(G_APPLICATION(ssf_app_new()), argc, argv);
}