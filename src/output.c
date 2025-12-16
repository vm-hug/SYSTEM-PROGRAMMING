#include <stdio.h>
#include <stdlib.h>

void redirect_output_to_file(const char *filepath) {
    if (filepath && filepath[0] != '\0') {
        FILE *fp = freopen(filepath, "w", stdout);
        if (!fp) {
            perror("Cannot open report file");
            exit(1);
        }
        // Vì stdout đã bị redirect, các lệnh printf sau này sẽ ghi vào file
    }
}