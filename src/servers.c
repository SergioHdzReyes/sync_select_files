#include "libssfservers.h"

char *config_file_path = NULL;
struct server_struct servers_list[100];
short servers_count = 0;

/**
 * Print instructions for command usage.
 */
void print_help() {
    char *program_name = "ssf-server";

    printf(_("Usage: %s [OPTION]...\n"), program_name);
    printf(_("Servers management, you can create, delete or edit them.\n"));
    printf("\n");

    printf(_("  -a, --add       add a new server\n"));
    printf(_("  -r, --remove    delete an existing server\n"));
    printf(_("  -e, --edit      edit an existing server\n"));
    printf("\n");
    printf(_("      --help     display this help and exit\n"));
    printf(_("      --version  output version information and exit\n"));

    exit(EXIT_SUCCESS);
}

/**
 * Process parameters passed to program.
 * @param argc Parameters quantity
 * @param argv Parameters array
 */
void parse_options(int argc, char *argv[], config_t *cfg) {
    int optc, item;
    char *str;
    enum {
        OPT_HELP,
        OPT_VERSION
    };

    static const struct option longopts[] = {
            {"add",     required_argument, NULL, 'a'},
            {"remove",  required_argument, NULL, 'r'},
            {"edit",    no_argument, NULL, 'e'},
            {"help",    no_argument, NULL, OPT_HELP},
            {"version", no_argument, NULL, OPT_VERSION},
            {NULL, 0,                NULL, 0}
    };

    while ((optc = getopt_long(argc, argv, "a:r:e", longopts, NULL)) != -1)
        switch (optc) {
            case OPT_VERSION:
                //version_etc (stdout, PROGRAM_NAME, PACKAGE_NAME, PACKAGE_VERSION, AUTHORS, (char *) NULL);
                exit(EXIT_SUCCESS);
            case OPT_HELP:
                print_help();
            case 'a':
                srvs_add_server(cfg, optarg);
                break;
            case 'r':
                item = (int) strtol(optarg, &str, 10);
                srvs_remove_server(cfg, item);
                break;
            case 'e':
                printf("EDIT\n");
                break;
            default:
                break;
        }
}

/**
 * Print a servers list to screen
 */
void show_servers_list() {
    printf("%-30s  %-30s  %-30s  %-30s  %-30s\n", "No.", "USER", "DOMAIN", "PORT", "PATH");

    for(int i = 0; i < servers_count; ++i)
    {
        printf("%-31d %-31s %-31s %-31d %-30s\n", servers_list[i].index+1, servers_list[i].user, servers_list[i].domain, servers_list[i].port, servers_list[i].path);
    }
    putchar('\n');
}


int main(int argc, char *argv[]) {
    config_t cfg;

    srvs_mgmt_init(&cfg);

    if (argc > 1) {
        parse_options(argc, argv, &cfg);
    } else {
        show_servers_list();
    }

    srvs_mgmt_end(&cfg);
    return EXIT_SUCCESS;
}
