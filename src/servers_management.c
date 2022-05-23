#include "servers_management.h"

void print_help ()
{
  char *program_name = "ssf-server";

  printf (_("Usage: %s [OPTION]...\n"), program_name);
  printf (_("Servers management, you can create, delete or edit them.\n"));
  printf ("\n");

  printf (_("  -a, --add       add a new server\n"));
  printf (_("  -r, --remove    delete an existing server\n"));
  printf (_("  -e, --edit      edit an existing server\n"));
  printf ("\n");
  printf (_("      --help     display this help and exit\n"));
  printf (_("      --version  output version information and exit\n"));
  
  exit(EXIT_SUCCESS);
}

void parse_options (int argc, char *argv[])
{
  int optc;
  enum {
    OPT_HELP,
    OPT_VERSION
  };
  
  static const struct option longopts[] = {
    {"add", no_argument, NULL, 'a'},
    {"remove", no_argument, NULL, 'r'},
    {"edit", no_argument, NULL, 'e'},
    {"help", no_argument, NULL, OPT_HELP},
    {"version", no_argument, NULL, OPT_VERSION},
    {NULL, 0, NULL, 0}
  };

  while ((optc = getopt_long (argc, argv, "are", longopts, NULL)) != -1)
    switch (optc)
      {
      case OPT_VERSION:
	//version_etc (stdout, PROGRAM_NAME, PACKAGE_NAME, PACKAGE_VERSION, AUTHORS, (char *) NULL);
	exit (EXIT_SUCCESS);
      case OPT_HELP:
	print_help ();
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

int configuration_init(config_t *cfg, const char *config_file)
{
  config_init(cfg);
  
  if (!check_config_file(cfg, config_file))
    {
      printf(_("An error has ocurred on configuration file reading\n"));
      exit(1);
    }

  return 0;
}

int check_config_file(config_t *cfg, const char *config_file)
{
  char config_path[100] = "";

  strcpy(config_path, "/home/sergio/config/");
  strcat(config_path, config_file);
  
  if(! config_read_file(cfg, config_path))
    return 0;
  else
    return 1;
}
