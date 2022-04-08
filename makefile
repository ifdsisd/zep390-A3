CC=gcc
CFLAGS= -g -O1

DEPS = part2.h projectlib.h
OBJ =  projectlib.o part2.o phypage.o pagetable.o


project: part1.c part2.c projectlib.c phypage.c pagetable.c
	$(CC) $(CFLAGS) -o part1 part1.c projectlib.c
	$(CC) $(CFLAGS)	-o part2 part2.c phypage.c pagetable.c projectlib.c