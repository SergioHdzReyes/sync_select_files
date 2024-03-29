#include <libconfig.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "general_utils.h"

#define _(STRING) gettext(STRING)

#define PROGRAM_NAME "ssf-servers"

#define CONFIG_FILE_NAME "ssf-servers.cfg"

struct server_struct {
    unsigned short index;
    char domain[50];
    unsigned short port;
    char path[100];
};

extern short servers_count;

extern struct server_struct servers_list[100];

extern char *config_file_path;

 /**
  * Add a new server to the config file
  * @param cfg Structure that contain config file info
  * @param url Url to save
  */
void add_server(config_t *cfg, char *url);

/**
 * Function that delete a server from config file.
 * @param cfg Structure that contain config file info
 * @param item Element to delete
 */
void remove_server(config_t *cfg, int item);

/**
 * Read user config file and populates servers_list[] array structure.
 * @param cfg Structure that contain config file info
 * @return
 */
void read_servers(config_t *cfg);

/**
 * Initialize all basic information.
 * @param cfg Structure that contain config file info
 * @return
 */
int servers_mgmt_init(config_t *cfg);

/**
 * Free up data structures and file descriptor related to config file.
 * @param cfg Structure that contain config file info
 * @return
 */
void servers_mgmt_end(config_t *cfg);

/**
 * Function that verify if ~/.config/ and ~/.config/config_file.cfg exists, if not, create it.
 * @param cfg Structure that contain config file info
 * @return void
 */
void check_config_file(config_t *cfg);
