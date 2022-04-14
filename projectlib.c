#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int mapAddress(unsigned long virtualAddress,unsigned long * physicalAddress,unsigned long * pageTable){
        //returns memory mapped physical address
        
        unsigned long index = virtualAddress >> 7;
        unsigned long offset = virtualAddress & 0x7f;
        // pushes frame offset to appropiate place and then OR's offset onto it
        unsigned long address = (pageTable[index] << 7 | offset);
        *physicalAddress = address;
        
        return 0;
}

int readFile(char * fileName,unsigned long** memoryTable){
    //writes contents of file onto memorytable buffer and returns bytes read
    
    struct stat st;
	unsigned long filesize;
    stat(fileName,&st);
    filesize=st.st_size;

    *memoryTable = (unsigned long*)  malloc(filesize);

 
    //loads addresses in file pointed to by bmemorytale, returns 1 on fail and 0 on success
    int fd_in;
    fd_in=open(fileName,O_RDONLY);
    if(fd_in == -1){
        fprintf(stderr,"File couldn't be read due to %s",strerror(errno));
        exit(errno);
    }
    if(read(fd_in,*memoryTable,(int)filesize) == -1){
        fprintf(stderr,"File couldn't be read correctly with error %s\n",strerror(errno));
        exit(errno);
    }
    close(fd_in);
    
    
    return filesize;
    




}
unsigned long getIndex(unsigned long address){
    return address >>7;
}