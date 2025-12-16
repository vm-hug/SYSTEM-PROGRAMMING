#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#include "dirstat.h"

static long file_cnt = 0, dir_cnt = 0;
static off_t total_size = 0;

void directory_stat(const char *path) {
    struct stat st;
    if (lstat(path, &st) != 0)
        return;

    if (S_ISREG(st.st_mode)) {
        file_cnt++;
        total_size += st.st_size;
        return;
    }

    if (!S_ISDIR(st.st_mode))
        return;

    dir_cnt++;
    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *ent;
    char buf[1024];

    while ((ent = readdir(dir)) != NULL) {
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
            continue;

        snprintf(buf, sizeof(buf), "%s/%s", path, ent->d_name);
        directory_stat(buf);
    }
    closedir(dir);

    printf("Files: %ld | Dirs: %ld | Size: %lld bytes\n",
           file_cnt, dir_cnt, (long long)total_size);
}
