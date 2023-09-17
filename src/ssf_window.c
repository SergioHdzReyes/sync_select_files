//
// Created by sergio on 2/10/22.
//

#include "ssf_window.h"
#include "ssf_select_server_dialog.h"
#include "ssf_invalid_project_dialog.h"

struct _SsfAppWindow {
    GtkApplicationWindow parent;

    GtkNotebook * bookEditors;
    SsfSelectServerDialog *selectServerDialog;
    SsfInvalidProjectDialog *invalidProjectDialog;

};

G_DEFINE_TYPE(SsfAppWindow, ssf_app_window, GTK_TYPE_APPLICATION_WINDOW);

void ssf_app_window_update_status (SsfAppWindow *pWindow);

static void ssf_app_window_init (SsfAppWindow *pWindow) {
    gtk_widget_init_template(GTK_WIDGET(pWindow));

    pWindow->selectServerDialog = NULL;
    pWindow->invalidProjectDialog = NULL;
}

static void ssf_app_window_class_init (SsfAppWindowClass *pClass) {
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(pClass), "/sync_select_files/ssf/ssf.AppWindow.glade");

    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfAppWindow, bookEditors);
}

SsfAppWindow * ssf_app_window_new (SsfApp *pApp) {
    SsfAppWindow * pWindow = g_object_new (SSF_APP_WINDOW_TYPE, "application", pApp, NULL);

    return pWindow;
}

/**
* SIGNALS
*/

void ssf_check_version_control(GtkWidget *widget, gpointer user_data)
{
    SsfAppWindow * pWindow = SSF_APP_WINDOW(user_data);
    gtk_widget_hide((GtkWidget *) pWindow);

    pWindow->invalidProjectDialog = ssf_invalid_project_dialog_new(pWindow, TRUE);
    gtk_window_present(GTK_WINDOW(pWindow->invalidProjectDialog));
}

void ssf_select_server_submenu(GtkMenuItem *menuitem, gpointer user_data) {
    SsfAppWindow * pWindow = SSF_APP_WINDOW(user_data);
    gtk_widget_hide((GtkWidget *) pWindow);

    pWindow->selectServerDialog = ssf_select_server_dialog_new(pWindow, TRUE, user_data);
    gtk_window_present(GTK_WINDOW(pWindow->selectServerDialog));
}
