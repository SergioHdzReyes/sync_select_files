//
// Created by sergio on 27/04/23.
//

#include "ssf_window.h"
#include "ssf_select_server_dialog.h"

struct _SsfSelectServerDialog {
    GtkDialog parent;

    SsfAppWindow * pWindow;

    GtkWidget * SMCancelBtn;
    GtkWidget * SMSelectBtn;
};

G_DEFINE_TYPE(SsfSelectServerDialog, ssf_select_server_dialog, GTK_TYPE_DIALOG);


static void ssf_select_server_dialog_init (SsfSelectServerDialog *pDialog) {
    gtk_widget_init_template(GTK_WIDGET(pDialog));
}

static void ssf_select_server_dialog_class_init (SsfSelectServerDialogClass *pClass) {
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(pClass), "/sync_select_files/ssf/ssf.ServersManagement.glade");

    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfSelectServerDialog, SMCancelBtn);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfSelectServerDialog, SMSelectBtn);
}

SsfSelectServerDialog * ssf_select_server_dialog_new (SsfAppWindow *pWindow, gboolean breplace) {
    SsfSelectServerDialog * pDialog = g_object_new(SSF_SELECT_SERVER_DIALOG_TYPE, "transient-for", pWindow, NULL);

    pDialog->pWindow = pWindow;

    return pDialog;
}
