#include <config.h>
#include <stdio.h>
#include <stdlib.h>

#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int main (void)
{
  /* Setting the i18n environment */
  setlocale(LC_ALL, "");
  bindtextdomain("hola", "/usr/share/locale/");
  textdomain("hola");

  printf(_("hola"));
  return EXIT_SUCCESS;
}
