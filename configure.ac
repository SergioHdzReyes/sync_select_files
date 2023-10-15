AC_INIT([sync_select_files], [0.1], [Sergio Hernandez <sergio.hdzreyes@gmail.com>])
AC_CONFIG_SRCDIR([src/ssf.c])
AM_INIT_AUTOMAKE([-Wall foreign])
AM_SILENT_RULES([yes])

AM_PROG_AR
LT_INIT

CC="gcc"
CFLAGS="-g -O0"
PKG_PROG_PKG_CONFIG

GLIB_GSETTINGS

PKG_CHECK_MODULES([GTK], [glib-2.0 gmodule-2.0 gtk+-3.0], , exit)
PKG_CHECK_MODULES([SOURCEVIEW], [gtksourceview-4], , exit)
PKG_CHECK_MODULES([LIBCONFIG], [libconfig >= 1.5],,
    AC_MSG_ERROR([libconfig 1.5 or newer not found.])
)

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])
AC_OUTPUT
