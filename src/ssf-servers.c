#include "servers_management.h"

int main(int argc, char *argv[]) {
    config_t cfg;
    //config_setting_t *setting;
    const char *config_file = "ssf-servers.cfg";
    char *config_file_path;

    configuration_init(&cfg, config_file, &config_file_path);

    if (argc > 1) {
        parse_options(argc, argv, &cfg, config_file_path);
    } else {
        show_servers_list(&cfg, config_file_path);
    }

    config_destroy(&cfg);
    return EXIT_SUCCESS;
}
