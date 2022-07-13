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

#define _(STRING) gettext(STRING)

#define PROGRAM_NAME "ssf-servers"

void print_help();

void parse_options(int argc, char *argv[]);

void show_servers_list(config_t *cfg, char *config_file_path);

int configuration_init(config_t *cfg, const char *config_file, char **config_file_path);

/**
 * Function that verify if ~/.config/ and ~/.config/config_file.cfg exists, if not, create it.
 * @param config_file Name of configuration file
 * @param config_file_path Full path of configuration file
 * @return void
 */
void check_config_file(const char *config_file, char **config_file_path);
