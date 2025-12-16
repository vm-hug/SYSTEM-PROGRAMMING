#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void start_watch(const char *path) {
    struct stat prev, current;
    
    if (stat(path, &prev) != 0) {
        perror("Watch init failed");
        return;
    }

    printf("👀 Watching changes for: %s (Ctrl+C to stop)\n", path);

    while (1) {
        sleep(1); // Poll mỗi 1 giây
        if (stat(path, &current) != 0) {
            printf("File deleted or inaccessible!\n");
            break;
        }

        if (current.st_mtime != prev.st_mtime) {
            printf("\n[ALERT] File changed at %s", ctime(&current.st_mtime));
            if (current.st_size != prev.st_size) {
                printf("Size changed: %ld -> %ld\n", (long)prev.st_size, (long)current.st_size);
            }
            prev = current; // Cập nhật trạng thái mới
        }
    }
}