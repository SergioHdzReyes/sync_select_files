#include "servers_management.h"

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

void parse_options(int argc, char *argv[]) {
    int optc;
    enum {
        OPT_HELP,
        OPT_VERSION
    };

    static const struct option longopts[] = {
            {"add",     no_argument, NULL, 'a'},
            {"remove",  no_argument, NULL, 'r'},
            {"edit",    no_argument, NULL, 'e'},
            {"help",    no_argument, NULL, OPT_HELP},
            {"version", no_argument, NULL, OPT_VERSION},
            {NULL, 0,                NULL, 0}
    };

    while ((optc = getopt_long(argc, argv, "are", longopts, NULL)) != -1)
        switch (optc) {
            case OPT_VERSION:
                //version_etc (stdout, PROGRAM_NAME, PACKAGE_NAME, PACKAGE_VERSION, AUTHORS, (char *) NULL);
                exit(EXIT_SUCCESS);
            case OPT_HELP:
                print_help();
            case 'a':
                printf("ADD\n");
                break;
            case 'r':
                printf("REMOVE\n");
                break;
            case 'e':
                printf("EDIT\n");
                break;
            default:
                break;
        }
}

int configuration_init(config_t *cfg, const char *config_file) {
    config_init(cfg);

    check_config_file(config_file);

    return 0;
}

void check_config_file(const char *config_file) {
    char *homedir = getenv("HOME");
    char config_path[100] = "";
    struct stat st = {0};

    strcpy(config_path, homedir);
    strcat(config_path, "/.config");

    if (stat(config_path, &st) == -1) {
        mkdir(config_path, 0666);
        printf(_("Directory %s created\n"), config_path);
    }

    strcat(config_path, "/");
    strcat(config_path, config_file);

    if (stat(config_path, &st) == -1) {
        printf(_("Configuration file don't exists!\nCreating it...\n"));
        int fd = open(config_path, O_RDWR | O_CREAT, 0644);

        if (fd != -1) {
            close(fd);
        } else {
            printf(_("Configuration file cannot be created exiting..."));
            exit(1);
        }
    }
}
