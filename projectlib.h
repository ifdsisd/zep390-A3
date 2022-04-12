#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int  mapAddress(unsigned long virtualAddress,unsigned long * physicalAddress,unsigned long * pageTable);

int readFile(char * fileName,unsigned long ** memoryTable);

unsigned long getIndex(unsigned long address);
