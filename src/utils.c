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
