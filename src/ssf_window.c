//
// Created by sergio on 2/10/22.
//

#include "ssf_window.h"
#include "ssf_select_server_dialog.h"
#include "ssf_invalid_project_dialog.h"
#include "ssf_diff_core.h"

struct _SsfAppWindow {
    GtkApplicationWindow parent;
    GApplication *app;

    GtkWidget *SsfGridDiffTools;
    GtkWidget *SsfGridDiffDifferences;

    /* Necessary for DiffTools */
    GtkWidget *SsfScrolledWindowFiles;
    GtkWidget *SsfGridAffectedFiles;

    GtkWidget *SsfListFiles;
    //GtkWidget *SsfFrameSourceCode;
    GtkWidget *SsfLocalFileDiff;
    GtkWidget *SsfRemoteFileDiff;
    GtkWidget *SsfContainerBox;

    SsfSelectServerDialog *selectServerDialog;
    SsfInvalidProjectDialog *invalidProjectDialog;

} AppWindow = {NULL};

G_DEFINE_TYPE(SsfAppWindow, ssf_app_window, GTK_TYPE_APPLICATION_WINDOW);

void ssf_app_window_update_status (SsfAppWindow *pWindow);

static void ssf_app_window_init (SsfAppWindow *pWindow) {
    gtk_widget_init_template(GTK_WIDGET(pWindow));
}

static void ssf_app_window_class_init (SsfAppWindowClass *pClass) {
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(pClass), "/sync_select_files/ssf/ssf.AppWindow.glade");

    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfAppWindow, SsfContainerBox);

    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfAppWindow, SsfGridDiffTools);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfAppWindow, SsfGridAffectedFiles);

    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfAppWindow, SsfGridDiffDifferences);
}

SsfAppWindow * ssf_app_window_new (GApplication *pApp) {
    AppWindow.app = pApp;
    SsfAppWindow * pWindow = g_object_new (SSF_APP_WINDOW_TYPE, "application", pApp, NULL);

    ssf_process_differences(pWindow);

    return pWindow;
}

void ssf_process_differences(SsfAppWindow *pWindow) {
    if (!ssf_diff_start()) {
        return;
    }

    GtkListStore *list_store;
    GtkTreeIter iter;
    gint i;
    //GtkWidget *checkbox[diff_count];

    list_store = gtk_list_store_new (5,
                                     G_TYPE_INT,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING);

    for (i = 0; i < diff_count; i++)
    {
        // Add a new row to the model
        gtk_list_store_append (list_store, &iter);
        //checkbox[i] = gtk_check_button_new_with_label("select");

        char *transaction;
        if (strcmp(operation[i], "del.") == 0) {
            transaction = "Eliminar";
        } else if (strcmp(operation[i], "send") == 0){
            transaction = "Enviar";
        } else {
            transaction = "Desconocido";
        }

        gtk_list_store_set (list_store, &iter,
                            0, i+1,
                            1, filepath[i],
                            2, transaction,
                            3, "Ver",
                            //4, checkbox[i],
                            4, "Seleccionar",
                            -1);
    }

    GtkWidget *tree_view = gtk_tree_view_new_with_model((GtkTreeModel *) list_store);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *number, *pathfile, *action, *see, *select;

    // First column
    number = gtk_tree_view_column_new_with_attributes("#", renderer, "text", 0, NULL);
    gtk_tree_view_append_column((GtkTreeView *) tree_view, number);

    // Second column
    pathfile = gtk_tree_view_column_new_with_attributes("Ruta de archivo", renderer, "text", 1, NULL);
    gtk_tree_view_append_column((GtkTreeView *) tree_view, pathfile);

    // Third column
    action = gtk_tree_view_column_new_with_attributes("Accion", renderer, "text", 2, NULL);
    gtk_tree_view_append_column((GtkTreeView *) tree_view, action);

    // Fourth column
    see = gtk_tree_view_column_new_with_attributes("Ver", renderer, "text", 3, NULL);
    gtk_tree_view_append_column((GtkTreeView *) tree_view, see);

    // Fifth column
    //GtkCellRenderer *toggle = gtk_cell_renderer_toggle_new();
    //select = gtk_tree_view_column_new_with_attributes("Seleccionar", toggle, 4, NULL);
    select = gtk_tree_view_column_new_with_attributes("Seleccionar", renderer, "text", 4, NULL);
    gtk_tree_view_append_column((GtkTreeView *) tree_view, select);

    gtk_grid_attach(GTK_GRID(pWindow->SsfGridAffectedFiles), tree_view, 0, 0, 1, 1);
    /* END DiffTools */

//    GtkSourceBuffer *buffer = gtk_source_buffer_new(NULL);
//
//    ssf_diff_start();
//
//    //ME QUEDE AQUI
//    gtk_text_buffer_set_text(&buffer->parent_instance, "Codigo de prueba", -1);
//
//    pWindow->SsfLocalFileDiff = gtk_source_view_new_with_buffer(buffer);
//
//    gtk_source_view_set_show_line_numbers((GtkSourceView *)pWindow->SsfLocalFileDiff, TRUE);
//    gtk_container_add((GtkContainer *) pWindow->SsfContainerBox, pWindow->SsfLocalFileDiff);
//
//    gtk_widget_show_all(pWindow->SsfGridDiffDifferences);
//    gtk_widget_show_all(pWindow->SsfLocalFileDiff);
    gtk_widget_show_all(pWindow->SsfGridAffectedFiles);
}

/**
* SIGNALS
*/

void ssf_check_version_control(GtkWidget *widget, gpointer user_data) {
    DIR *dir = opendir(".git");

    if (dir) {
        closedir(dir);
        return;
    }

    SsfAppWindow * pWindow = SSF_APP_WINDOW(user_data);
    gtk_widget_hide((GtkWidget *) pWindow);

    pWindow->invalidProjectDialog = ssf_invalid_project_dialog_new(pWindow, TRUE, AppWindow.app);
    gtk_window_present(GTK_WINDOW(pWindow->invalidProjectDialog));
}

void ssf_select_server_submenu(GtkMenuItem *menuitem, gpointer user_data) {
    SsfAppWindow * pWindow = SSF_APP_WINDOW(user_data);
    gtk_widget_hide((GtkWidget *) pWindow);

    pWindow->selectServerDialog = ssf_select_server_dialog_new(pWindow, TRUE, user_data);
    gtk_window_present(GTK_WINDOW(pWindow->selectServerDialog));
}

void ssf_app_submenu_exit(GtkMenuItem *menuitem, gpointer user_data)
{
    g_application_quit(AppWindow.app);
}
