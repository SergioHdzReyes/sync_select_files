//
// Created by sergio on 16/09/23.
//

#ifndef SYNC_SELECT_FILES_SSF_INVALID_PROJECT_DIALOG_H
#define SYNC_SELECT_FILES_SSF_INVALID_PROJECT_DIALOG_H

#define SSF_INVALID_PROJECT_DIALOG_TYPE (ssf_invalid_project_dialog_get_type ())
G_DECLARE_FINAL_TYPE (SsfInvalidProjectDialog, ssf_invalid_project_dialog, SSF, INVALID_PROJECT_DIALOG, GtkDialog)

SsfInvalidProjectDialog * ssf_invalid_project_dialog_new(SsfAppWindow * pWindow, gboolean breplace, GApplication *gApp);

void ssf_invalid_project_dlg_accept(GtkButton *accept_btn, gpointer user_data);

#endif //SYNC_SELECT_FILES_SSF_INVALID_PROJECT_DIALOG_H
