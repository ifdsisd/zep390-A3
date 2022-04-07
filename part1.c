#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char * argv[]){

    u_int64_t  pageTable[]={2,4,1,7,3,5,6};
    char * fileName;
    char * outputFile;
    int fd_in,fd_out;
    struct stat st;
    u_int64_t filesize;
    
    u_int64_t * memAccesses;
    int i;


    if(argc != 3){
        fprintf(stderr,"Usage: %s <infile> <outfile>\n",argv[0]);
        exit(0);
    }

    fileName = argv[1];
    outputFile = argv[2];
	stat(fileName, &st);
	filesize = st.st_size;
	//allocate space for all addresses
	memAccesses = (u_int64_t*) malloc( (size_t) filesize );
    fd_in = open(fileName,O_RDONLY);
    if(fd_in == -1){
        fprintf(stderr,"file couldn't be accessed with error %d\n",strerror(errno));
        exit(-1);
    }

    read(fd_in,memAccesses,(int)filesize);
    close(fd_in);


// file IO
    fd_out = open(outputFile,O_WRONLY|O_CREAT|O_TRUNC,0444);
    if (fd_out == -1){
        fprintf(stderr,"File couldn't be written with error %s\n",strerror(errno)); 
    }

    for(int x=0;x<filesize/sizeof(u_int64_t);x++){
        u_int64_t virtualAddress = memAccesses[x];
        u_int64_t page = virtualAddress >> 7;
        u_int64_t offset = virtualAddress & 0x7f;
        // pushes frame offset to appropiate place and then OR's offset onto it
        u_int64_t frameOffset = (pageTable[page] << 7) | offset;
        u_int64_t * p_frame = &frameOffset;


        if (write(fd_out,p_frame,sizeof(frameOffset)) == -1){
            fprintf(stderr,"Unable to write to file with error %s\n",strerror(errno));
        }
        printf("Virtual Page Address-> %#010lx Frame Page Address -> %#010lx\n",virtualAddress,frameOffset);
    
    }
    close(fd_out);
    free(memAccesses);

    return 0;
}