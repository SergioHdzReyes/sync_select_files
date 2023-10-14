//
// Created by sergio on 27/04/23.
//

#include "ssf_window.h"
#include "ssf_select_server_dialog.h"

config_t cfg;

char *config_file_path = NULL;
struct server_struct servers_list[100];
short servers_count = 0;
short selected_server;

GtkWidget *serversRadioBtn[100] = {NULL};

struct _SsfSelectServerDialog {
    GtkDialog parent;

    SsfAppWindow * pWindow;
    GtkGrid *SMServersListGrid;

    GtkWidget * SMCancelBtn;
    GtkWidget * SMSelectBtn;
};

gpointer *parentData;

G_DEFINE_TYPE(SsfSelectServerDialog, ssf_select_server_dialog, GTK_TYPE_DIALOG);


static void ssf_select_server_dialog_init (SsfSelectServerDialog *pDialog) {
    gtk_widget_init_template(GTK_WIDGET(pDialog));
}

static void ssf_select_server_dialog_class_init (SsfSelectServerDialogClass *pClass) {
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(pClass), "/sync_select_files/ssf/ssf.ServersManagement.glade");

    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfSelectServerDialog, SMCancelBtn);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfSelectServerDialog, SMSelectBtn);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfSelectServerDialog, SMServersListGrid);
}

SsfSelectServerDialog * ssf_select_server_dialog_new (SsfAppWindow *pWindow, gboolean breplace, gpointer parent_data) {
    parentData = parent_data;
    SsfSelectServerDialog * pDialog = g_object_new(SSF_SELECT_SERVER_DIALOG_TYPE, "transient-for", pWindow, NULL);

    srvs_mgmt_init(&cfg);
    signed char sel_server = srvs_selected_server(&cfg);

    if (servers_count) {
        char url[160];
        sprintf(url, "%s:%d/%s", servers_list[0].domain, servers_list[0].port, servers_list[0].path);

        serversRadioBtn[0] = gtk_radio_button_new_with_label(NULL, url);
        gtk_grid_insert_row(pDialog->SMServersListGrid, 0);
        gtk_grid_attach(GTK_GRID(pDialog->SMServersListGrid), serversRadioBtn[0], 1, 0, 2, 1);

        if (sel_server == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(serversRadioBtn[0]), TRUE);
        }

        for (int i = 1; i < servers_count; ++i) {
            sprintf(url, "%s:%d/%s", servers_list[i].domain, servers_list[i].port, servers_list[i].path);

            gtk_grid_insert_row(pDialog->SMServersListGrid, i);

            serversRadioBtn[i] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(serversRadioBtn[0]), url);
            gtk_grid_attach(GTK_GRID(pDialog->SMServersListGrid), serversRadioBtn[i], 1, i, 2, 1);

            if ((sel_server >= 1) && (sel_server == i)){
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(serversRadioBtn[i]), TRUE);
            }
        }

        gtk_widget_show_all((GtkWidget *) pDialog->SMServersListGrid);
    }

    pDialog->pWindow = pWindow;
    return pDialog;
}

/**
 * SIGNALS
 */
void ssf_select_server_dlg_cancel(GtkButton *cancel_btn, gpointer user_data) {
    SsfSelectServerDialog * pDialog = SSF_SELECT_SERVER_DIALOG(user_data);
    srvs_mgmt_end(&cfg);

    gtk_window_close(GTK_WINDOW(pDialog));

    SsfAppWindow * pWindow = SSF_APP_WINDOW(parentData);
    gtk_widget_show((GtkWidget *) pWindow);
}

void ssf_select_server_dlg_select(GtkButton *select_btn, gpointer user_data) {
    SsfSelectServerDialog * pDialog = SSF_SELECT_SERVER_DIALOG(user_data);

    for (int i = 0; i < servers_count; ++i) {
        if (gtk_toggle_button_get_active((GtkToggleButton *)serversRadioBtn[i])) {
            selected_server = (short) i;
        }
    }

    gtk_window_close(GTK_WINDOW(pDialog));

    SsfAppWindow * pWindow = SSF_APP_WINDOW(parentData);
    gtk_widget_show((GtkWidget *) pWindow);

    srvs_select_server(&cfg, selected_server);
    srvs_mgmt_end(&cfg);
}
