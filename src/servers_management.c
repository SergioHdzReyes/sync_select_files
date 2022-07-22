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

void parse_options(int argc, char *argv[], config_t *cfg, char *config_file_path) {
    int optc, item;
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

    while ((optc = getopt_long(argc, argv, "are", longopts, NULL)) != -1)
        switch (optc) {
            case OPT_VERSION:
                //version_etc (stdout, PROGRAM_NAME, PACKAGE_NAME, PACKAGE_VERSION, AUTHORS, (char *) NULL);
                exit(EXIT_SUCCESS);
            case OPT_HELP:
                print_help();
            case 'a':
                add_server(cfg, optarg, config_file_path);
                break;
            case 'r':
                sscanf(optarg, "%d", &item);
                remove_server(cfg, item, config_file_path);
                break;
            case 'e':
                printf("EDIT\n");
                break;
            default:
                break;
        }
}

void show_servers_list(config_t *cfg, char *config_file_path) {
    if(! config_read_file(cfg, config_file_path))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(cfg),
                config_error_line(cfg), config_error_text(cfg));
        config_destroy(cfg);
        exit(1);
    }

    config_setting_t *setting;

    setting = config_lookup(cfg, "servers");
    if(setting != NULL)
    {
        int count = config_setting_length(setting);
        int i;

        printf("%-30s  %-30s  %-30s  %-30s\n", "No.", "DOMAIN", "PORT", "PATH");

        for(i = 0; i < count; ++i)
        {
            config_setting_t *server = config_setting_get_elem(setting, i);
            const char *domain, *path;
            int port;

            if(!(config_setting_lookup_string(server, "domain", &domain)
                 && config_setting_lookup_string(server, "path", &path)
                 && config_setting_lookup_int(server, "port", &port)))
                continue;

            printf("%-31d %-31s %-31d %-30s\n", i + 1, domain, port, path);
        }
        putchar('\n');
    }
}

void add_server(config_t *cfg, char *url, char *config_file_path) {
    struct url_struct server_info;
    config_setting_t  *setting, *root, *server;

    server_info = parse_url(url);

    root = config_root_setting(cfg);
    setting = config_setting_get_member(root, "servers");
    server = config_setting_add(setting, NULL, CONFIG_TYPE_GROUP);

    setting = config_setting_add(server, "domain", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, server_info.domain);

    setting = config_setting_add(server, "port", CONFIG_TYPE_INT);
    config_setting_set_int(setting, server_info.port);

    setting = config_setting_add(server, "path", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, server_info.path);

    if(! config_write_file(cfg, config_file_path)) {
        fprintf(stderr, "Error while writing file.\n");
        config_destroy(cfg);
        exit(EXIT_FAILURE);
    }

    printf(_("Server added successfully\n"));
}

void remove_server(config_t *cfg, int item, char *config_file_path) {
    config_setting_t *setting;

    setting = config_lookup(cfg, "servers");
    if(setting != NULL) {
        int count = config_setting_length(setting);

        if (!count) {
            printf(_("There are not elements to remove."));
        } else if((item <= 0) || (item > count)) {
            printf(_("Element not found.\n"));
        } else {
            config_setting_remove_elem(setting, --item);

            if(! config_write_file(cfg, config_file_path)) {
                fprintf(stderr, "Error while writing file.\n");
                config_destroy(cfg);
                exit(EXIT_FAILURE);
            }

            printf(_("Server removed successfully\n"));
        }
    }
}

int configuration_init(config_t *cfg, const char *config_file, char **config_file_path) {
    config_init(cfg);

    check_config_file(config_file, config_file_path, cfg);

    return 0;
}

void check_config_file(const char *config_file, char **config_file_path, config_t *cfg) {
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

    if (!config_read_file(cfg, config_path)) {
        printf(_("Configuration file don't exists!\nCreating it...\n"));
        int fd = open(config_path, O_RDWR | O_CREAT, 0644);

        if (fd != -1) {
            close(fd);
        } else {
            printf(_("Configuration file cannot be created exiting..."));
            exit(1);
        }
    }

    *config_file_path = malloc(sizeof(char) * (strlen(config_path) + 1));
    strcpy(*config_file_path, config_path);
}
