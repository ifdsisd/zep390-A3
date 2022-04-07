#include <stdlib.h>
#include <sys/types.h>
#include "pagetable.h"

int pageFaults=0;

pageEntry * initialize(){
// return a preinited page table
    pageEntry * entry = malloc(sizeof(pageEntry)*TABLE_SIZE);
    // frame number unknown so not set
    for(int x=0;x<TABLE_SIZE;x++){
        entry[x].valid=0;
        entry[x].reference=0;
    }

    return entry;
    
void enterAddress(pageEntry *pageTable,u_int32_t enter_address){
    //inputs address into page table and counts faults

}







}