#include <string.h>
#include "options.h"
#include "dispatcher.h"

int main(int argc, char *argv[]) {
    int idx = 1;

    /* SỬA LỖI:
       Cho phép parse_options chạy nếu tham số KHÔNG bắt đầu bằng "--" 
       HOẶC nếu tham số chính xác là "--audit" 
    */
    if (argc > 1 && (strncmp(argv[1], "--", 2) != 0 || strcmp(argv[1], "--audit") == 0)) {
        parse_options(argc, argv, &idx);
    }

    dispatch(argc, argv, idx);
    return 0;
}