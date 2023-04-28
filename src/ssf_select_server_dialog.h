//
// Created by sergio on 27/04/23.
//

#ifndef SYNC_SELECT_FILES_SSF_SELECT_SERVER_DIALOG_H
#define SYNC_SELECT_FILES_SSF_SELECT_SERVER_DIALOG_H

#define SSF_SELECT_SERVER_DIALOG_TYPE (ssf_select_server_dialog_get_type ())
G_DECLARE_FINAL_TYPE (SsfSelectServerDialog, ssf_select_server_dialog, SSF, SELECT_SERVER_DIALOG, GtkDialog)

SsfSelectServerDialog * ssf_select_server_dialog_new(SsfAppWindow * pWindow, gboolean breplace);

#endif //SYNC_SELECT_FILES_SSF_SELECT_SERVER_DIALOG_H
