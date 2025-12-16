#include <unistd.h>
#include <stdio.h>
#include "options.h"

int opt_all = 0, opt_recursive = 0, opt_follow = 0, opt_human = 0;
int opt_find = 0, opt_compare = 0, opt_stat = 0;
int opt_find_name = 0, opt_find_size = 0;

char find_name[128];
long find_size = 0;

void parse_options(int argc, char *argv[], int *path_index) {
    int c;
    while ((c = getopt(argc, argv, "aRLh")) != -1) {
        switch (c) {
            case 'a': opt_all = 1; break;
            case 'R': opt_recursive = 1; break;
            case 'L': opt_follow = 1; break;
            case 'h': opt_human = 1; break;
            default:
                printf("Usage: %s [-aRLh] <path>\n", argv[0]);
                _exit(1);
        }
    }
    *path_index = optind;
}