#include <stdio.h>
#include <sys/stat.h>

#include "compare.h"

void compare_files(const char *f1, const char *f2) {
    struct stat a, b;

    if (stat(f1, &a) || stat(f2, &b)) {
        perror("stat");
        return;
    }

    printf("Attribute        %s        %s\n", f1, f2);
    printf("Size             %ld        %ld\n", a.st_size, b.st_size);
    printf("Permission       %o         %o\n", a.st_mode & 0777, b.st_mode & 0777);
    printf("Inode            %lu        %lu\n", a.st_ino, b.st_ino);
    printf("Links            %u         %u\n", a.st_nlink, b.st_nlink);
}
