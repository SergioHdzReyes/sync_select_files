//
// Created by sergio on 07/05/23.
//

#ifndef SYNC_SELECT_FILES_SSF_DIFF_CORE_H
#define SYNC_SELECT_FILES_SSF_DIFF_CORE_H

extern char operation[500][100];
extern char filepath[500][100];

extern short int diff_count;

int ssf_diff_start();

void ssf_diff_finish();

int process_command();

//void ssf_diff_get_file();


#endif //SYNC_SELECT_FILES_SSF_DIFF_CORE_H
