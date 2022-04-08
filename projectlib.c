#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int mapAddress(u_int32_t virtualAddress,u_int32_t * physicalAddress,u_int32_t * pageTable){
        //returns memory mapped physical address
        
        u_int32_t index = virtualAddress >> 7;
        u_int32_t offset = virtualAddress & 0x7f;
        // pushes frame offset to appropiate place and then OR's offset onto it
        u_int32_t address = (pageTable[index] << 7 | offset);
        *physicalAddress = address;
        
        return 0;
}

int readFile(char * fileName,u_int32_t** memoryTable){
    //writes contents of file onto memorytable buffer
    
    struct stat st;
	u_int32_t filesize;
    stat(fileName,&st);
    filesize=st.st_size;

    double l =2;
    *memoryTable = (u_int32_t*)  malloc(filesize);

 
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
u_int32_t getIndex(u_int32_t address){
    return address >>7;
}
