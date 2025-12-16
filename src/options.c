#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "options.h"

// Khởi tạo biến
int opt_all = 0, opt_recursive = 0, opt_follow = 0, opt_human = 0;
int opt_find = 0, opt_compare = 0, opt_stat = 0, opt_audit = 0;
int opt_find_name = 0, opt_find_size = 0;

// MỚI
int opt_watch = 0;
char output_path[256] = "";
int opt_sort_type = 0; // 0: none, 1: name, 2: size, 3: time

// Biến cho find
char find_name[128];
long find_size = 0;

void parse_options(int argc, char *argv[], int *path_index) {
    // Xử lý --audit, --watch, --sort, --output ở đây (Long options manual)
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--audit") == 0) {
            opt_audit = 1;
            if (i + 1 < argc) *path_index = i + 1;
            return; 
        }
        if (strcmp(argv[i], "--watch") == 0) {
            opt_watch = 1;
            if (i + 1 < argc) *path_index = i + 1;
            return;
        }
        if (strncmp(argv[i], "--sort=", 7) == 0) {
            char *type = argv[i] + 7;
            if (strcmp(type, "name") == 0) opt_sort_type = 1;
            else if (strcmp(type, "size") == 0) opt_sort_type = 2;
            else if (strcmp(type, "time") == 0) opt_sort_type = 3;
            continue; // Không return để parse tiếp các flag khác
        }
        if (strcmp(argv[i], "--output") == 0 && i + 1 < argc) {
            strcpy(output_path, argv[i+1]);
            i++; // Skip path
            continue;
        }
    }

    // Các short option cũ
    optind = 1; // Reset getopt
    int c;
    while ((c = getopt(argc, argv, "aRLh")) != -1) {
        switch (c) {
            case 'a': opt_all = 1; break;
            case 'R': opt_recursive = 1; break;
            case 'L': opt_follow = 1; break;
            case 'h': opt_human = 1; break;
        }
    }
    *path_index = optind;
    // Fix lại nếu optind trỏ vào flag sort/output
    while (*path_index < argc && argv[*path_index][0] == '-') {
        (*path_index)++;
    }
}