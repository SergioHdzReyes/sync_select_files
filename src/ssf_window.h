//
// Created by sergio on 2/10/22.
//

#ifndef SYNC_SELECT_FILES_SSF_WINDOW_H
#define SYNC_SELECT_FILES_SSF_WINDOW_H

#include "ssf.h"
#include "ssf_app.h"

#define SSF_APP_WINDOW_TYPE (ssf_app_window_get_type ())
G_DECLARE_FINAL_TYPE (SsfAppWindow, ssf_app_window, SSF, APP_WINDOW, GtkApplicationWindow)

#include "servers_mgmt.h"

extern short selected_server;

SsfAppWindow * ssf_app_window_new (SsfApp *pApp);

#endif //SYNC_SELECT_FILES_SSF_WINDOW_H
