#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include "search.h"
#include "options.h"

static void match_and_print(const char *path, struct stat *st) {
    if (opt_find_name && strstr(path, find_name))
        printf("%s\n", path);

    if (opt_find_size && st->st_size > find_size)
        printf("%s\n", path);
}

void search_path(const char *path) {
    struct stat st;
    if (lstat(path, &st) != 0)
        return;

    if (S_ISREG(st.st_mode))
        match_and_print(path, &st);

    if (!S_ISDIR(st.st_mode))
        return;

    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *ent;
    char buf[1024];

    while ((ent = readdir(dir)) != NULL) {
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
            continue;

        snprintf(buf, sizeof(buf), "%s/%s", path, ent->d_name);
        search_path(buf);
    }

    closedir(dir);
}
