#define SIZE 7
#define ENTRIES 32
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "pagetable.h"
#include "phypage.h"
#include "projectlib.h"












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
    
    

    for(int entry=0;entry<memoryEntries;entry++){
        // *addresses, memory read from file
        // virtAddress memory with valid bit ,frame number,and reference counter 
        unsigned long virtAddress = addresses[entry];
        unsigned long index = getIndex(virtAddress);
        // load up and update page entry
        
        
        
        
        
       
        
        // frames are still availible
        if (currentFrame()<8 ){
       
            virtTable[index].frameNumber=currentFrame();
        
        
        
            if(virtTable[index].valid == 0){
                virtTable[index].valid=1;
                printf("Page Fault\n");
                pageFaults++;
            }
            else{
                virtTable[index].reference=currentRef();
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
                // printf("Mem Addr: %#010lx : Frame %d taken from Index %d : new Index at %d\t",virtAddress,virtTable[lowestRefIndex].frameNumber,lowestRefIndex,index);
                // printf("Reference updated to %d\n",currentRef());
            }


           

        }
        
        updateRef();
        
               

    }
    


    



    // enterAddress(pageTable,address);
  
    free(virtTable);
    free(addresses);

    printf("Number of page faults %d\n",pageFaults);

    return 0;
}