#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include "security.h"

static void audit_file(const char *path) {
    struct stat st;
    if (lstat(path, &st) != 0) return;

    if (st.st_mode & S_ISUID)
        printf("[!] SUID file: %s\n", path);

    if ((st.st_mode & 0777) == 0777)
        printf("[!] World-writable: %s\n", path);

    const char *home = getenv("HOME");
    /* THÊM ĐIỀU KIỆN: S_ISREG(st.st_mode) để chỉ tìm file, bỏ qua thư mục */
    if (home && strstr(path, home) &&
        S_ISREG(st.st_mode) &&   // <--- Chỉ báo nếu là file thường
        (st.st_mode & S_IXUSR))
        printf("[!] Executable in HOME: %s\n", path);
}

void audit_path(const char *path) {
    struct stat st;
    if (lstat(path, &st) != 0) return;

    audit_file(path);

    if (!S_ISDIR(st.st_mode)) return;

    DIR *d = opendir(path);
    if (!d) return;

    struct dirent *e;
    char buf[1024];

    while ((e = readdir(d))) {
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, ".."))
            continue;

        snprintf(buf, sizeof(buf), "%s/%s", path, e->d_name);
        audit_path(buf);
    }
    closedir(d);
}
