#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdio.h>

extern int opt_all, opt_recursive, opt_follow, opt_human, opt_find, opt_compare, opt_stat;
extern int opt_find_name, opt_find_size;
extern int opt_audit;
extern char find_name[128];
extern long find_size;


extern int opt_watch;         
extern char output_path[256]; 
extern int opt_sort_type;     

void parse_options(int argc, char *argv[], int *path_index);

#endif
