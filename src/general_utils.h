//
// Created by Sergio Hernández on 03/02/18.
//

#ifndef SYNC_SELECT_FILES_GENERAL_UTILS_H
#define SYNC_SELECT_FILES_GENERAL_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <memory.h>

struct url_struct {
    char domain[50];
    int port;
    char path[100];
};

/**
 * Add an element to array
 *
 * @param array Pointer to the array element on memory
 * @param index Index for maintain size on memory
 * @return void
 */
void add_array_element(char **array, int *index);

/**
 * Verify if the given path is a regular file or directory.
 * The returned value we'll be true for a regular file or false for a directory.
 *
 * @param path Path to analize
 * @return integer
 */
int is_regular_file(const char *path);

/**
 * Process and validate a url string
 * @param url Url string
 * @return Struct containing the url fields
 */
struct url_struct parse_url(char *url);

#endif //SYNC_SELECT_FILES_GENERAL_UTILS_H
