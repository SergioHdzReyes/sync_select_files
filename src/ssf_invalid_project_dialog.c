//
// Created by sergio on 16/09/23.
//

#include "ssf_window.h"
#include "ssf_invalid_project_dialog.h"

struct _SsfInvalidProjectDialog {
    GtkDialog parent;
    SsfAppWindow * pWindow;
    GApplication *app;

    GtkWidget * AcceptBtn;
} dialog;

G_DEFINE_TYPE(SsfInvalidProjectDialog, ssf_invalid_project_dialog, GTK_TYPE_DIALOG);

static void ssf_invalid_project_dialog_init (SsfInvalidProjectDialog *pDialog) {
    gtk_widget_init_template(GTK_WIDGET(pDialog));
}

static void ssf_invalid_project_dialog_class_init (SsfInvalidProjectDialogClass *pClass) {
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(pClass), "/sync_select_files/ssf/gui/InvalidProjectDialog.glade");

    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfInvalidProjectDialog, AcceptBtn);
}

SsfInvalidProjectDialog * ssf_invalid_project_dialog_new (SsfAppWindow *pWindow, gboolean breplace, GApplication * gApp) {
    dialog.app = gApp;
    SsfInvalidProjectDialog * pDialog = g_object_new(SSF_INVALID_PROJECT_DIALOG_TYPE, "transient-for", pWindow, NULL);

    gtk_widget_show_all((GtkWidget *) pDialog);

    pDialog->pWindow = pWindow;
    return pDialog;
}

/**
 * SIGNALS
 */
void ssf_invalid_project_dlg_terminate(GtkButton *accept_btn, gpointer user_data)
{
    g_application_quit(dialog.app);
}
