#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "dirwalk.h"
#include "fileinfo.h"
#include "options.h"

void walk_directory(const char *path, int depth) {
    DIR *d = opendir(path);
    if (!d) return;

    struct dirent *e;
    while ((e = readdir(d))) {
        if (!opt_all && e->d_name[0] == '.') continue;

        for (int i = 0; i < depth; i++) printf("│   ");
        printf("├── %s\n", e->d_name);

        char full[4096];
        snprintf(full, sizeof(full), "%s/%s", path, e->d_name);

        print_file_info(full);

        struct stat st;
        if (opt_recursive &&
            lstat(full, &st) == 0 &&
            S_ISDIR(st.st_mode) &&
            strcmp(e->d_name, ".") &&
            strcmp(e->d_name, "..")) {
            walk_directory(full, depth + 1);
        }
    }
    closedir(d);
}
