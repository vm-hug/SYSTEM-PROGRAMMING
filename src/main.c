#include <string.h>
#include "options.h"
#include "dispatcher.h"

int main(int argc, char *argv[]) {
    int idx = 1;

    if(argc > 1) {
        parse_options(argc, argv, &idx);
    }else {
        idx = 1;
    }

    if (idx >= argc && !opt_find && !opt_watch && !opt_compare) {
        static char *dot[] = { "fileexplorer", "." };
        argv = dot;
        argc = 2;
        idx = 1;
    }

    dispatch(argc, argv, idx);
    return 0;
}
