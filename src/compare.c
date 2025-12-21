#include <stdio.h>
#include <sys/stat.h>

#include "compare.h"

void compare_files(const char *f1, const char *f2) {
    struct stat a, b;

    if (stat(f1, &a) || stat(f2, &b)) {
        perror("stat");
        return;
    }


    printf("\n"); 
    printf("%-12s %-25s %-25s\n", "Attribute", f1, f2);
    printf("--------------------------------------------------------------\n");
    
    printf("%-12s %-25ld %-25ld\n", "Size", (long)a.st_size, (long)b.st_size);
    
    printf("%-12s %-25o %-25o\n", "Permission", a.st_mode & 0777, b.st_mode & 0777);
    
    printf("%-12s %-25lu %-25lu\n", "Inode", (unsigned long)a.st_ino, (unsigned long)b.st_ino);
    
    printf("%-12s %-25u %-25u\n", "Links", (unsigned int)a.st_nlink, (unsigned int)b.st_nlink);
    printf("\n");
}