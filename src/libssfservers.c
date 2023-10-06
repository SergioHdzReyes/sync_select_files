#include "libssfservers.h"

unsigned short fd;

void srvs_add_server(config_t *cfg, char *url) {
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

void srvs_remove_server(config_t *cfg, int item) {
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

void srvs_read_servers(config_t *cfg) {
    config_setting_t *setting;

    setting = config_lookup(cfg, "servers");
    if(setting != NULL)
    {
        int count = config_setting_length(setting);
        int i;

        for(i = 0; i < count; ++i)
        {
            config_setting_t *server = config_setting_get_elem(setting, i);
            const char *domain, *path;
            int port;

            if(!(config_setting_lookup_string(server, "domain", &domain)
                 && config_setting_lookup_string(server, "path", &path)
                 && config_setting_lookup_int(server, "port", &port)))
                continue;

            servers_list[i].index = i;
            strcpy(servers_list[i].domain, domain);
            servers_list[i].port = port;
            strcpy(servers_list[i].path, path);
        }
        servers_count = (short) i;
    }
}

int srvs_mgmt_init(config_t *cfg) {
    config_init(cfg);

    srvs_check_cfg_file(cfg);

    srvs_read_servers(cfg);

    return 0;
}

void srvs_mgmt_end(config_t *cfg) {
    config_destroy(cfg);

    close(fd);
}

void srvs_check_cfg_file(config_t *cfg) {
    char config_path[100] = "";

    if (!srvs_config_dir_exists((char *) &config_path)) {
        mkdir(config_path, 0666);
        printf(_("Directory %s created\n"), config_path);
    }

    strcat(config_path, "/");
    strcat(config_path, CONFIG_FILE_NAME);

    if (!config_read_file(cfg, config_path)) {
        printf(_("Configuration file don't exists!\nCreating it...\n"));
        fd = open(config_path, O_RDWR | O_CREAT, 0644);

        if (!fd) {
            printf(_("Configuration file cannot be created exiting..."));
            exit(1);
        }
    }

    config_file_path = malloc(sizeof(char) * (strlen(config_path) + 1));
    strcpy(config_file_path, config_path);
}

int srvs_config_dir_exists(char *dir)
{
    char *homedir = getenv("HOME");
    char config_path[100] = "";
    struct stat st = {0};

    strcpy(config_path, homedir);
    strcat(config_path, "/.config");

    strcpy(dir, config_path);

    if (stat(config_path, &st) == -1) {
        return 0;
    }

    return 1;
}

int srvs_check_empty_list(config_t *cfg)
{
    char config_path[100];

    if (!srvs_config_dir_exists((char *) &config_path)) {
        return 1;
    }

    strcat(config_path, "/");
    strcat(config_path, CONFIG_FILE_NAME);

    if (!config_read_file(cfg, config_path)) {
        return 1;
    }

    config_setting_t *setting;

    setting = config_lookup(cfg, "servers");
    if(setting != NULL)
    {
        if (!config_setting_length(setting))
            return 1;
    } else {
        return 1;
    }

    return 0;
}
