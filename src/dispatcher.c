#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "dispatcher.h"
#include "options.h"
#include "dirwalk.h"
#include "fileinfo.h"
#include "search.h"
#include "compare.h"
#include "dirstat.h"

void dispatch(int argc, char *argv[], int idx) {

    /* ===== --compare ===== */
    if (idx < argc && strcmp(argv[idx], "--compare") == 0) {
        if (idx + 2 >= argc) {
            printf("Usage: %s --compare <file1> <file2>\n", argv[0]);
            return;
        }
        compare_files(argv[idx + 1], argv[idx + 2]);
        return;
    }

    /* ===== --stat ===== */
    if (idx < argc && strcmp(argv[idx], "--stat") == 0) {
        if (idx + 1 >= argc) {
            printf("Usage: %s --stat <path>\n", argv[0]);
            return;
        }
        directory_stat(argv[idx + 1]);
        return;
    }

    /* ===== --find ===== */
    if (idx < argc && strcmp(argv[idx], "--find") == 0) {
        if (idx + 1 >= argc) {
            printf("Usage: %s --find name=xxx | size>xxx\n", argv[0]);
            return;
        }

        opt_find = 1;

        if (strncmp(argv[idx + 1], "name=", 5) == 0) {
            opt_find_name = 1;
            strcpy(find_name, argv[idx + 1] + 5);
        }
        else if (strncmp(argv[idx + 1], "size>", 5) == 0) {
            opt_find_size = 1;
            find_size = atol(argv[idx + 1] + 5);
        }
        else {
            printf("Invalid find condition\n");
            return;
        }

        search_path(".");
        return;
    }

    /* ===== FALLBACK: tree + file info ===== */
    if (idx >= argc) {
        printf("Missing path\n");
        return;
    }

    struct stat st;
    lstat(argv[idx], &st);

    printf("Directory Structure:\n");
    printf("%s\n", argv[idx]);

    if (S_ISDIR(st.st_mode))
        walk_directory(argv[idx], 0);
    else
        print_file_info(argv[idx]);
}
