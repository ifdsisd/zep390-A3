#define SIZE 7
#define ENTRIES 32
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "pagetable.h"
#include "phypage.h"
#include "projectlib.h"







unsigned long  pageTable[SIZE]={2,4,1,7,3,5,6};




int main(int argc,char * argv[]){


    pageEntry*   virtTable = initialize(); 
    // need to modify array itself later
    unsigned long * addresses=NULL;
    int pageFaults=0;
    
    
    char * fileName;
    char * outputFile;
    fileName = argv[1];
    outputFile=argv[2];
    

    if(argc != 3){
            fprintf(stderr,"Usage: %s <infile> <outfile>\n",argv[0]);
            exit(1);
        }
    


    size_t memoryEntries = readFile(fileName,&addresses);

    memoryEntries=memoryEntries / sizeof(unsigned long);
    int fd_out = open(outputFile,O_WRONLY|O_CREAT|O_TRUNC,0666);
    if (fd_out == -1){
        fprintf(stderr,"File couldn't be written with error %s\n",strerror(errno)); 
    }
    

    for(int entry=0;entry<memoryEntries;entry++){
        // *addresses, memory read from file
        // virtAddress memory with valid bit ,frame number,and reference counter 
        unsigned long virtAddress = addresses[entry];
        unsigned long  phyAddress =0;
        unsigned long offset = 0;
        unsigned long index = getIndex(virtAddress);
        

        
        
        // load up and update page entry
        
        
        
        
       
        
        // frames are still availible
        if (currentFrame()<8 ){
       
            
        
            
        
            if(virtTable[index].valid == 0){

                phyAddress = currentFrame() << 7;
                offset = virtAddress & 0x7f;
                phyAddress = phyAddress | offset;


                virtTable[index].valid=1;
                printf("Page Fault %d\n",pageFaults);
                pageFaults++;
                virtTable[index].reference=currentRef();
                virtTable[index].frameNumber=currentFrame();
                printf("Current Frame is: %d\n",currentFrame());
                printf("Virtual Address is: %#10lx ----->",virtAddress);
                printf("Physical Address is: %#010lx\n",phyAddress);
            }
            nextFrame();
        }
        //otherwise... swapping ensues
        else{


            if(virtTable[index].valid==1){

                virtTable[index].reference=currentRef();
                // printf("Matching page found at %d\n",index);

            }
            else{


                pageFaults++;
                unsigned long lowestRefIndex = lowestRef(virtTable,32,index);//could need fixin
                // printf("Swapping out least recently used frame at %d\t",virtTable[lowestRefIndex].frameNumber);
                // printf("Valid bit of oldest frame is %d\n",virtTable[lowestRefIndex].valid);
                //invalidates
                virtTable[lowestRefIndex].valid=0;  
                // validates stealer
                virtTable[index].valid=1;
                //steals frame
                virtTable[index].frameNumber = virtTable[lowestRefIndex].frameNumber;
                virtTable[index].reference=currentRef();
                //
            }
            phyAddress = virtTable[index].frameNumber << 7;
            offset = virtAddress & 0x7f;
            phyAddress = phyAddress | offset;

           

        }
        
        
        updateRef();
        
        if (write(fd_out,&phyAddress,sizeof(unsigned long)) == -1){
            fprintf(stderr,"Unable to write to file with error %s\n",strerror(errno));
            exit(1);
        }
               

    }
    
    

    close(fd_out);
    



    // enterAddress(pageTable,address);
  
    free(virtTable);
    free(addresses);

    printf("Number of page faults %d\n",pageFaults);

    return 0;
}