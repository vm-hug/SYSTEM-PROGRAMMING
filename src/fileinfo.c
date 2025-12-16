#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <unistd.h>
#include "fileinfo.h"
#include "utils.h"
#include "options.h"
#include "bsdinfo.h"

void print_file_info(const char *path) {
    struct stat st;
    if ((opt_follow ? stat : lstat)(path, &st) != 0) {
        perror(path);
        return;
    }

    char perm[11], tbuf[64], sbuf[32];
    mode_to_rwx(st.st_mode, perm);
    print_time(st.st_mtime, tbuf, sizeof(tbuf));
    human_size(st.st_size, sbuf, sizeof(sbuf));

    printf("Path: %s\n", path);
    printf("Type: %s\n",
        S_ISREG(st.st_mode) ? "Regular" :
        S_ISDIR(st.st_mode) ? "Directory" :
        S_ISLNK(st.st_mode) ? "Symlink" :
        S_ISCHR(st.st_mode) ? "Char Dev" :
        S_ISBLK(st.st_mode) ? "Block Dev" :
        S_ISSOCK(st.st_mode)? "Socket" : "FIFO");

    printf("Perm: %s (%o)\n", perm, mode_to_octal(st.st_mode));
    printf("Owner: %s\n", getpwuid(st.st_uid)->pw_name);
    printf("Group: %s\n", getgrgid(st.st_gid)->gr_name);
    printf("Size: %s\n", opt_human ? sbuf : "bytes");
    printf("Inode: %lu | Links: %lu\n",
        (unsigned long)st.st_ino,
        (unsigned long)st.st_nlink);
    printf("Modified: %s\n", tbuf);
    printf("--------------NEW----------------\n");
    print_permission_bits(st.st_mode);
    print_special_bits(st.st_mode);
    print_bsd_flags(&st);
    print_birth_time(&st);
    printf("---------------------------------\n");
}
