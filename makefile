CC=gcc
CFLAGS= -O1 -g -o

DEPS = part2.h projectlib.h


project: part1.c part2.c projectlib.c phypage.c pagetable.c
	$(CC) $(CFLAGS) part1 part1.c projectlib.c
	$(CC) $(CFLAGS) part2 part2.c phypage.c pagetable.c projectlib.c