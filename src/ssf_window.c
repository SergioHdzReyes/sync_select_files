//
// Created by sergio on 2/10/22.
//

#include "ssf_window.h"

struct _SsfAppWindow {
    GtkApplicationWindow parent;

    GtkNotebook * bookEditors;
};

G_DEFINE_TYPE(SsfAppWindow, ssf_app_window, GTK_TYPE_APPLICATION_WINDOW);

void ssf_app_window_update_status (SsfAppWindow *pWindow);

static void ssf_app_window_init (SsfAppWindow *pWindow) {
    gtk_widget_init_template(GTK_WIDGET(pWindow));
}

static void ssf_app_window_class_init (SsfAppWindowClass *pClass) {
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(pClass), "/sync_select_files/ssf/ssf.SsfAppWindow.glade");

    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfAppWindow, bookEditors);
}

SsfAppWindow * ssf_app_window_new (SsfApp *pApp) {
    SsfAppWindow * pWindow = g_object_new (SSF_APP_WINDOW_TYPE, "application", pApp, NULL);

    return pWindow;
}
