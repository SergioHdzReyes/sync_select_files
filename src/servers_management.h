#include <libconfig.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <libintl.h>
#include <locale.h>
#include <string.h>

#define _(STRING) gettext(STRING)

#define PROGRAM_NAME "ssf-servers"

void print_help();

void parse_options(int argc, char *argv[]);

int configuration_init(config_t *cfg, const char *config_file);

int check_config_file(config_t *cfg, const char *config_file);
