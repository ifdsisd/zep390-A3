#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int  mapAddress(u_int32_t virtualAddress,u_int32_t * physicalAddress,u_int32_t * pageTable);

int readFile(char * fileName,u_int32_t ** memoryTable);

u_int32_t getIndex(u_int32_t address);
