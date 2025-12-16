#ifndef OPTIONS_H
#define OPTIONS_H

extern int opt_all, opt_recursive, opt_follow, opt_human , opt_find , opt_compare , opt_stat , opt_find_name , opt_find_size;
extern char find_name[128];
extern long find_size;

void parse_options(int argc, char *argv[], int *path_index);

#endif