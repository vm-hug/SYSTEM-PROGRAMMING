#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"

void mode_to_rwx(mode_t m, char *b) {
    b[0] = S_ISDIR(m) ? 'd' : S_ISLNK(m) ? 'l' : '-';
    char rwx[] = "rwx";
    for (int i = 0; i < 9; i++)
        b[i+1] = (m & (1 << (8 - i))) ? rwx[i%3] : '-';
    b[10] = 0;
}

int mode_to_octal(mode_t m) {
    return m & 0777;
}

void human_size(off_t s, char *b, size_t l) {
    const char *u = "BKMGT";
    int i = 0;
    double d = s;
    while (d >= 1024 && i < 4) { d /= 1024; i++; }
    snprintf(b, l, "%.1f%c", d, u[i]);
}

void print_time(time_t t, char *b, size_t l) {
    strftime(b, l, "%Y-%m-%d %H:%M", localtime(&t));
}

void print_permission_bits(mode_t m) {
    char p[11] = "----------";

    if (S_ISDIR(m)) p[0] = 'd';
    if (S_ISLNK(m)) p[0] = 'l';

    if (m & S_IRUSR) p[1] = 'r';
    if (m & S_IWUSR) p[2] = 'w';
    if (m & S_IXUSR) p[3] = 'x';

    if (m & S_IRGRP) p[4] = 'r';
    if (m & S_IWGRP) p[5] = 'w';
    if (m & S_IXGRP) p[6] = 'x';

    if (m & S_IROTH) p[7] = 'r';
    if (m & S_IWOTH) p[8] = 'w';
    if (m & S_IXOTH) p[9] = 'x';


    if (m & S_ISUID) p[3] = (p[3] == 'x') ? 's' : 'S';
    if (m & S_ISGID) p[6] = (p[6] == 'x') ? 's' : 'S';
    if (m & S_ISVTX) p[9] = (p[9] == 'x') ? 't' : 'T';

    printf("Perm: %s\n", p);
}

void print_special_bits(mode_t m) {
    printf("Special bits:");
    int found = 0;

    if (m & S_ISUID) {
        printf(" SUID");
        found = 1;
    }
    if (m & S_ISGID) {
        printf(" SGID");
        found = 1;
    }
    if (m & S_ISVTX) {
        printf(" Sticky");
        found = 1;
    }

    if (!found)
        printf(" none");

    printf("\n");
}
