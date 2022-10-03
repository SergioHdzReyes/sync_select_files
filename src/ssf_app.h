//
// Created by sergio on 2/10/22.
//

#ifndef SYNC_SELECT_FILES_SSF_APP_H
#define SYNC_SELECT_FILES_SSF_APP_H

#include "ssf.h"

#define SSF_APP_TYPE (ssf_app_get_type ())
G_DECLARE_FINAL_TYPE (SsfApp, ssf_app, SSF, APP, GtkApplication)

SsfApp * ssf_app_new (void);
static void ssf_app_activate (GApplication * pApp);

#endif //SYNC_SELECT_FILES_SSF_APP_H
