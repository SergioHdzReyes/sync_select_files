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

    GtkWidget *SsfDiffGridMain;
    GtkWidget *SsfListFiles;
    //GtkWidget *SsfFrameSourceCode;
    GtkWidget *SsfLocalFileDiff;
    GtkWidget *SsfRemoteFileDiff;
    GtkWidget *SsfContainerBox;

    SsfSelectServerDialog *selectServerDialog;
    SsfInvalidProjectDialog *invalidProjectDialog;

} AppWindow;

G_DEFINE_TYPE(SsfAppWindow, ssf_app_window, GTK_TYPE_APPLICATION_WINDOW);

void ssf_app_window_update_status (SsfAppWindow *pWindow);

static void ssf_app_window_init (SsfAppWindow *pWindow) {
    gtk_widget_init_template(GTK_WIDGET(pWindow));

    pWindow->selectServerDialog = NULL;
    pWindow->invalidProjectDialog = NULL;
}

static void ssf_app_window_class_init (SsfAppWindowClass *pClass) {
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(pClass), "/sync_select_files/ssf/ssf.AppWindow.glade");

    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfAppWindow, SsfDiffGridMain);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pClass), SsfAppWindow, SsfContainerBox);
}

SsfAppWindow * ssf_app_window_new (GApplication *pApp) {
    AppWindow.app = pApp;
    SsfAppWindow * pWindow = g_object_new (SSF_APP_WINDOW_TYPE, "application", pApp, NULL);

    //process_differences(pWindow);

    return pWindow;
}

void ssf_process_differences(SsfAppWindow *pWindow) {
    GtkSourceBuffer *buffer = gtk_source_buffer_new(NULL);

    ssf_diff_start();

    //ME QUEDE AQUI
    gtk_text_buffer_set_text(&buffer->parent_instance, "Codigo de prueba", -1);

    pWindow->SsfLocalFileDiff = gtk_source_view_new_with_buffer(buffer);

    gtk_source_view_set_show_line_numbers((GtkSourceView *)pWindow->SsfLocalFileDiff, TRUE);
    gtk_container_add((GtkContainer *) pWindow->SsfContainerBox, pWindow->SsfLocalFileDiff);

    // Comienza mostrar archivos
    enum {
        COLUMN_INT,
        COLUMN_STRING,
        COLUMN_INT2,
        N_COLUMNS
    };
    GtkListStore *list_store = gtk_list_store_new(N_COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT);
    GtkTreeIter iter;
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter,
                       COLUMN_INT, 1,
                       COLUMN_STRING, "SERGIO",
                       COLUMN_INT2, 1234,
                       -1);

    GtkWidget *tree_view = gtk_tree_view_new_with_model((GtkTreeModel *) list_store);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    GtkTreeViewColumn *number, *filename;
    number = gtk_tree_view_column_new_with_attributes("Numero", renderer, "text", 0, NULL);
    filename = gtk_tree_view_column_new_with_attributes("Nombre de archivo", renderer, NULL);
    gtk_tree_view_append_column((GtkTreeView *) tree_view, number);
    gtk_tree_view_append_column((GtkTreeView *) tree_view, filename);

    gtk_grid_attach(GTK_GRID(pWindow->SsfDiffGridMain), tree_view, 1, 1, 1, 1);
    // Termina mostrar archivos

    gtk_widget_show_all(pWindow->SsfDiffGridMain);
    gtk_widget_show_all(pWindow->SsfLocalFileDiff);
}

/**
* SIGNALS
*/

void ssf_check_version_control(GtkWidget *widget, gpointer user_data)
{
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
