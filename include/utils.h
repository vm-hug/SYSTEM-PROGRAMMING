#ifndef UTILS_H
#define UTILS_H

#include <sys/types.h>

void mode_to_rwx(mode_t mode, char *buf);
int mode_to_octal(mode_t mode);
void human_size(off_t size, char *buf, size_t len);
void print_time(time_t t, char *buf, size_t len);

#endif