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
    u_int32_t  mapper[SIZE]={2,4,1,7,3,5,6};
    // need to modify array itself later
    u_int32_t * addresses=NULL;
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

    memoryEntries=memoryEntries / sizeof(u_int32_t);
    
    

    for(int entry=0;entry<memoryEntries;entry++){
        // *addresses, memory read from file
        // virtAddress memory with valid bit ,frame number,and reference counter 
        u_int32_t virtAddress = addresses[entry];
        u_int32_t index = getIndex(virtAddress);
        // load up and update page entry
        
        
        
        
       
        
        // frames are still availible
        if (currentFrame()<8 ){
       
            virtTable[index].frameNumber=currentFrame();
        
        
        
            if(virtTable[index].valid == 0){
                virtTable[index].valid=1;
                pageFaults++;
            }
            else{
                virtTable[index].reference=currentRef();
            }
            
        }
        //otherwise... conflict ensues
        else{
            
            
            if(virtTable[index].valid==0){
                u_int32_t lowestRefIndex = lowestRef(virtTable,memoryEntries,index);
                //invalidates
                virtTable[lowestRefIndex].valid=0;
                // validates stealer
                virtTable[index].valid=1;
                //steals frame
                virtTable[index].frameNumber = virtTable[lowestRefIndex].frameNumber;
                virtTable[index].reference=currentRef();
                //
            
            }
            else{
                virtTable[index].reference=currentRef();
            }
            //finds LRU
         
           

        }
        nextFrame();
        updateRef();
        printf("Frame overview valid: %x frame: %x reference:%x\n",virtTable[index].valid,virtTable[index].frameNumber,virtTable[index].reference) ;       
        printf("Sanity checks  table index:\t%x Index:\t%x\n",virtTable[index],index);
        printf("Sanity checks  memory location:\t%x \n",virtAddress);
        printf("====================================================================");
                printf("====================================================================");

    }
    


    



    // enterAddress(pageTable,address);
  
  
    free(virtTable);
    free(addresses);



    return 0;
}