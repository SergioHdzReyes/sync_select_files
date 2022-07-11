#include "servers_management.h"

int main(int argc, char *argv[]) {
    config_t cfg;
    //config_setting_t *setting;
    const char *config_file = "ssf-servers.cfg";

    configuration_init(&cfg, config_file);

    parse_options(argc, argv);

    return EXIT_SUCCESS;
}
