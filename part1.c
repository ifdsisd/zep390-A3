#define SIZE 7

#include <stdio.h> 
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "projectlib.h"

unsigned long  pageTable[SIZE]={2,4,1,7,3,5,6};


int main(int argc, char * argv[]){

    char * fileName;
    char * outputFile;
    int fd_out;
    unsigned long * memAccesses;


    if(argc != 3){
        fprintf(stderr,"Usage: %s <infile> <outfile>\n",argv[0]);
        exit(1);
    }

    fileName = argv[1];
    outputFile = argv[2];
	
	//allocate space for all addresses

    
    size_t filesize = readFile(fileName,&memAccesses);
    if(filesize == -1){
        fprintf(stderr,"Error occured during reading Error:%s",strerror(errno));
        exit(1);
    }

// file IO
   
    fd_out = open(outputFile,O_WRONLY|O_CREAT|O_TRUNC,0666);
    if (fd_out == -1){
        fprintf(stderr,"File couldn't be written with error %s\n",strerror(errno)); 
    }

    for(unsigned long x=0;x<filesize/(sizeof(unsigned long));x++){
        unsigned long  virtualAddress = memAccesses[x];
        unsigned long  physicalOffset = 0;
        mapAddress(virtualAddress,&physicalOffset,pageTable);

        
        if (write(fd_out,&physicalOffset,sizeof(unsigned long)) == -1){
            fprintf(stderr,"Unable to write to file with error %s\n",strerror(errno));
            exit(1);
        }
        printf("Virtual Page Address-> %#010lx Frame Page Address -> %#010lx\n",virtualAddress,physicalOffset);
        
        printf("%d\n",x);
    }
    close(fd_out);
    
    free(memAccesses);

    return 0;
}