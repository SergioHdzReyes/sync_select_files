AC_INIT([Sync Select Files],
[0.1],
[sergio.hdzreyes@gmail.com],
[sync-select-files],
[https://github.com/SergioHdzReyes/sync_select_files])

dnl Must come before AM_INIT_AUTOMAKE.
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([
	1.11.1
	readme-alpha
	subdir-objects
	-Wall -Werror
])

dnl Version minima de Autoconf requerida
AC_PREREQ([2.69])

AC_CONFIG_SRCDIR([src/ssf.c])

AC_PROG_CC

dnl Since we use gnulib: gl_EARLY must be called as soon as possible after
dnl the C compiler is checked.  The others could be later, but we just
dnl keep everything together.
gl_EARLY
gl_INIT

# Checks for libraries.

# Checks for header files.
AC_CONFIG_HEADERS([config.h:config.in])
AC_CHECK_HEADERS([memory.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
# AC_FUNC_MALLOC
# AC_FUNC_REALLOC

PKG_CHECK_MODULES([GTK], [glib-2.0 gmodule-2.0 gtk+-3.0], , exit)
PKG_CHECK_MODULES([SOURCEVIEW], [gtksourceview-4], , exit)

dnl i18n support from GNU gettext.
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.19.8])

AC_CONFIG_FILES([
Makefile
src/Makefile
])

AC_OUTPUT
