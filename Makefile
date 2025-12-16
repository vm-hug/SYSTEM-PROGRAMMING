CC=cc
CFLAGS=-Wall -Wextra -Iinclude

OBJS = src/main.o src/options.o src/dispatcher.o src/fileinfo.o src/dirwalk.o src/utils.o src/search.o src/compare.o src/dirstat.o src/security.o src/bsdinfo.o src/watch.o src/output.o src/sort.o

fileexplorer: $(OBJS)
	$(CC) $(CFLAGS) -o fileexplorer $(OBJS) -lutil

clean:
	rm -f $(OBJS) fileexplorer