#include <dirent.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <stdio.h>
#include "options.h"

char parent_path_sort[1024];

int sort_compare(const struct dirent **a, const struct dirent **b) {
    struct stat s1, s2;
    char p1[2048], p2[2048];

    if (opt_sort_type == 1) {
        return strcasecmp((*a)->d_name, (*b)->d_name);
    }

    snprintf(p1, sizeof(p1), "%s/%s", parent_path_sort, (*a)->d_name);
    snprintf(p2, sizeof(p2), "%s/%s", parent_path_sort, (*b)->d_name);
    lstat(p1, &s1);
    lstat(p2, &s2);

    if (opt_sort_type == 2) {
        return (s2.st_size - s1.st_size); 
    }

    if (opt_sort_type == 3) {
        return (s2.st_mtime - s1.st_mtime); 
    }

    return 0;
}