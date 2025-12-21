#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include "bsdinfo.h"

void print_bsd_flags(struct stat *st) {
    printf("BSD Flags: ");
    int found = 0;

#if defined(UF_NODUMP)
    if (st->st_flags & UF_NODUMP) { printf("nodump "); found=1; }
#endif
#if defined(UF_IMMUTABLE)
    if (st->st_flags & UF_IMMUTABLE) { printf("immutable "); found=1; }
#endif
#if defined(UF_APPEND)
    if (st->st_flags & UF_APPEND) { printf("append-only "); found=1; }
#endif
#if defined(UF_OPAQUE)
    if (st->st_flags & UF_OPAQUE) { printf("opaque "); found=1; }
#endif

    if (!found) printf("none");
    printf("\n");
}

void print_birth_time(struct stat *st) {
    char buf[64];
    struct tm *tm = localtime(&st->st_birthtime);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", tm);
    printf("Birth Time: %s\n", buf);
}