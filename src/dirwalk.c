#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "options.h"
#include "fileinfo.h"
#include "sort.h" 

extern char parent_path_sort[1024]; 

void walk_directory(const char *path, int depth) {
    struct dirent **namelist;
    int n;

    strcpy(parent_path_sort, path);

    if (opt_sort_type > 0) {
        n = scandir(path, &namelist, NULL, sort_compare);
    } else {
        n = scandir(path, &namelist, NULL, alphasort);
    }

    if (n < 0) return;

    for (int i = 0; i < n; i++) {
        struct dirent *e = namelist[i];

        if (!opt_all && e->d_name[0] == '.') {
            free(e); continue;
        }
        if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0) {
            free(e); continue;
        }

        for (int k = 0; k < depth; k++) printf("│   ");
        
        char full[4096];
        snprintf(full, sizeof(full), "%s/%s", path, e->d_name);
        
        struct stat st;
        lstat(full, &st);

        if (S_ISDIR(st.st_mode)) 
            printf("├── \033[1;34m📁 %s\033[0m\n", e->d_name); 
        else if (st.st_mode & S_IXUSR) 
            printf("├── \033[1;32m🚀 %s\033[0m\n", e->d_name);
        else 
            printf("├── \033[0;37m📄 %s\033[0m\n", e->d_name); 

        if (opt_recursive && S_ISDIR(st.st_mode)) {
            walk_directory(full, depth + 1);
        }
        free(e);
    }
    free(namelist);
}
