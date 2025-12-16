#ifndef BSDINFO_H
#define BSDINFO_H
#include <sys/stat.h>

void print_bsd_flags(struct stat *st);
void print_birth_time(struct stat *st);

#endif