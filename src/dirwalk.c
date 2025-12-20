#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "options.h"
#include "fileinfo.h"
#include "sort.h" // Include file sort mới

extern char parent_path_sort[1024]; // Lấy biến từ sort.c

void walk_directory(const char *path, int depth) {
    struct dirent **namelist;
    int n;

    // Thiết lập đường dẫn cha để sort.c dùng stat()
    strcpy(parent_path_sort, path);

    // Dùng scandir để lấy danh sách và sort luôn
    if (opt_sort_type > 0) {
        n = scandir(path, &namelist, NULL, sort_compare);
    } else {
        n = scandir(path, &namelist, NULL, alphasort); // Mặc định a-z
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

        // --- TREE ĐẸP + MÀU SẮC ---
        for (int k = 0; k < depth; k++) printf("│   ");
        
        char full[4096];
        snprintf(full, sizeof(full), "%s/%s", path, e->d_name);
        
        struct stat st;
        lstat(full, &st);

        // Icon & Màu (ANSI code)
        if (S_ISDIR(st.st_mode)) 
            printf("├── \033[1;34m📁 %s\033[0m\n", e->d_name); // Xanh dương
        else if (st.st_mode & S_IXUSR) 
            printf("├── \033[1;32m🚀 %s\033[0m\n", e->d_name); // Xanh lá (exe)
        else 
            printf("├── \033[0;37m📄 %s\033[0m\n", e->d_name); // Trắng

        // In chi tiết file (nếu không phải mode tree thuần)
        // print_file_info(full); <--- Tuỳ bạn muốn in chi tiết luôn hay chỉ tree

        // Đệ quy
        if (opt_recursive && S_ISDIR(st.st_mode)) {
            walk_directory(full, depth + 1);
        }
        free(e);
    }
    free(namelist);
}
