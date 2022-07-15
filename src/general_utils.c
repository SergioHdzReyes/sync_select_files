#include "general_utils.h"

void add_array_element(char **array, int *index) {
    (*index)++;
    array = realloc(array, (*index) * sizeof(array));
}

int is_regular_file(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);

    return S_ISREG(path_stat.st_mode);
}

struct url_struct parse_url(char *url) {
    struct url_struct url_parsed;

    char ip[50];
    int port = 80;
    char path[100];
    sscanf(url, "http://%49[^:]:%99d/%99[^\n]", ip, &port, path);

    strcpy(url_parsed.ip, ip);
    url_parsed.port = port;
    strcpy(url_parsed.path, path);

    return url_parsed;
}