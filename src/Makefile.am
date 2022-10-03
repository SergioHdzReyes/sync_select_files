AM_CFLAGS = $(GTK_CFLAGS) $(SOURCEVIEW_CFLAGS)

bin_PROGRAMS = ssf ssf-servers
ssf_SOURCES = ssf.c ssf_app.c ssf_window.c
ssf_servers_SOURCES = ssf-servers.c servers_management.c general_utils.c

ssf_LDADD = $(LIBINTL) $(GTK_LIBS) $(SOURCEVIEW_LIBS)
ssf_servers_LDADD = -lconfig
ssf_servers_LDFLAGS = -g
