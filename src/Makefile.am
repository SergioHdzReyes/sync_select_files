AM_CFLAGS = $(GTK_CFLAGS) $(SOURCEVIEW_CFLAGS)
AM_CPPFLAGS = -DLOCALEDIR=\""$(localedir)"\" -rdynamic
bin_PROGRAMS = ssf ssf-servers

ssf_LDADD = $(GTK_LIBS) $(SOURCEVIEW_LIBS) -lconfig
ssf_LDFLAGS = -g
ssf_SOURCES = ssf.gresources.h \
ssf.gresources.c \
ssf.c \
ssf_app.c \
ssf_window.c \
ssf_select_server_dialog.c \
servers_mgmt.c \
general_utils.c

ssf_servers_LDADD = -lconfig
ssf_servers_LDFLAGS = -g
ssf_servers_SOURCES = servers.c servers_mgmt.c general_utils.c

ssf.gresources.c: ssf.gresources.xml ssf.AppWindow.glade ssf.ServersManagement.glade ssf.gresources.h
	$(AM_V_GEN) glib-compile-resources --generate-source $<

ssf.gresources.h: ssf.gresources.xml ssf.AppWindow.glade ssf.ServersManagement.glade
	$(AM_V_GEN) glib-compile-resources --generate-header $<

gsettings_SCHEMAS = sync_select_files.ssf.gschema.xml
EXTRA_DIST = $(gsettings_SCHEMAS)

@GSETTINGS_RULES@
