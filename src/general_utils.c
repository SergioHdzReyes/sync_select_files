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
