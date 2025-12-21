#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "options.h"

int opt_all = 0, opt_recursive = 0, opt_follow = 0, opt_human = 0;
int opt_find = 0, opt_compare = 0, opt_stat = 0, opt_audit = 0;
int opt_find_name = 0, opt_find_size = 0;

int opt_watch = 0;
char output_path[256] = "";
int opt_sort_type = 0; 

char find_name[128];
long find_size = 0;

void parse_options(int argc, char *argv[], int *path_index) {
    int i;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--audit") == 0) { 
            opt_audit = 1; 
            *path_index = (i+1 < argc) ? i+1 : i; return; 
        }
        if (strcmp(argv[i], "--watch") == 0) {
             opt_watch = 1; *path_index = (i+1 < argc) ? i+1 : i; return; 
            }
        if (strcmp(argv[i], "--stat") == 0) { 
            opt_stat = 1; *path_index = i; return; 
        }
        if (strcmp(argv[i], "--compare") == 0) { 
            opt_compare = 1; *path_index = i; return; 
        }
        if (strcmp(argv[i], "--find") == 0) { 
            opt_find = 1; *path_index = i; return; 
        }

        if (strncmp(argv[i], "--sort=", 7) == 0) {
            char *type = argv[i] + 7;
            if (strcmp(type, "name") == 0) opt_sort_type = 1;
            else if (strcmp(type, "size") == 0) opt_sort_type = 2;
            else if (strcmp(type, "time") == 0) opt_sort_type = 3;
            continue;
        }

        if (strncmp(argv[i], "--output=", 9) == 0) {
            strcpy(output_path, argv[i] + 9);
            continue;
        }
        if (strcmp(argv[i], "--output") == 0 && i + 1 < argc) {
            strcpy(output_path, argv[i+1]);
            i++; 
            continue;
        }
    }

    optind = 1;
    opterr = 0; 
    int c;
    while ((c = getopt(argc, argv, "aRLh")) != -1) {
        switch (c) {
            case 'a': opt_all = 1; break;
            case 'R': opt_recursive = 1; break;
            case 'L': opt_follow = 1; break;
            case 'h': opt_human = 1; break;
        }
    }
    
    *path_index = 1; 
    while (*path_index < argc) {
        if (strcmp(argv[*path_index], "--output") == 0) {
            *path_index += 2; 
            continue;
        }

        if (strncmp(argv[*path_index], "--output=", 9) == 0 || 
            strncmp(argv[*path_index], "--sort=", 7) == 0) {
            (*path_index)++;
            continue;
        }

        if (argv[*path_index][0] == '-') {
            (*path_index)++;
            continue;
        }
        
        break; 
    }
}