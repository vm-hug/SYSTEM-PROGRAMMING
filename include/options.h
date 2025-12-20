#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdio.h>

// Các biến cũ
extern int opt_all, opt_recursive, opt_follow, opt_human, opt_find, opt_compare, opt_stat;
extern int opt_find_name, opt_find_size;
extern int opt_audit;
extern char find_name[128];
extern long find_size;

// --- MỚI THÊM CHO PHẦN NÂNG CAO ---
extern int opt_watch;         // D1
extern char output_path[256]; // D2
extern int opt_sort_type;     // E2: 0=none, 1=name, 2=size, 3=time

void parse_options(int argc, char *argv[], int *path_index);

#endif
