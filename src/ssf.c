#include "ssf.h"
#include "ssf_app.h"

int main( int argc, char *argv[] ) {
    return g_application_run(G_APPLICATION(ssf_app_new()), argc, argv);
}