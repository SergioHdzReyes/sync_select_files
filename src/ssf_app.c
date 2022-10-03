//
// Created by sergio on 2/10/22.
//

#include "ssf_app.h"
#include "ssf_window.h"

struct _SsfApp {
    GtkApplication parent;
};

G_DEFINE_TYPE(SsfApp, ssf_app, GTK_TYPE_APPLICATION)

static void ssf_app_init (SsfApp * pApp) {}

static void ssf_app_activate (GApplication * pApp) {
    SsfAppWindow * pWindow;

    pWindow = ssf_app_window_new(SSF_APP(pApp));
    gtk_window_present (GTK_WINDOW(pWindow));
}

static void ssf_app_class_init(SsfAppClass *class)
{
    G_APPLICATION_CLASS (class)->activate = ssf_app_activate;
}

SsfApp * ssf_app_new (void) {
    SsfApp * pApp = NULL;

    pApp = g_object_new (SSF_APP_TYPE, "application-id", "sync_select_files", "flags", G_APPLICATION_HANDLES_OPEN, NULL);

    return pApp;
}
