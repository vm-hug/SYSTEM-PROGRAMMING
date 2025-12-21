#include <stdio.h>
#include <stdlib.h>

void redirect_output_to_file(const char *filepath) {
    if (filepath && filepath[0] != '\0') {
        FILE *fp = freopen(filepath, "w", stdout);
        if (!fp) {
            perror("Cannot open report file");
            exit(1);
        }
    }
}