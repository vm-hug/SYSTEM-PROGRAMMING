#include <string.h>
#include "options.h"
#include "dispatcher.h"

int main(int argc, char *argv[]) {
    int idx = 1;

    /* Nếu là long option (--xxx) thì bỏ qua getopt */
    if (argc > 1 && strncmp(argv[1], "--", 2) != 0) {
        parse_options(argc, argv, &idx);
    }

    dispatch(argc, argv, idx);
    return 0;
}
