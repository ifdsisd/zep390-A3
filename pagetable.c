#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "pagetable.h"

int referenceBit=0;

pageEntry * initialize(){
// return a preinited page table
    pageEntry * entry = malloc(sizeof(pageEntry)*TABLE_SIZE);
    // frame number unknown so not set
    for(int x=0;x<TABLE_SIZE;x++){
        entry[x].valid=0;
        entry[x].frameNumber=-1;
        entry[x].reference=0;
    }

    return entry;
}    

u_int32_t lowestRef(pageEntry * table,u_int32_t length,u_int32_t page_num){
    //TODO print table in entirity ensure it's working fine
    u_int32_t lowest=table[0].reference;
    u_int32_t index=0;
    for(int x=1;x<length;x++){
        printf("Index: %d Value: %d\n",x,table[x].reference);
        //finds lowest and prevents replacing itself
        if(lowest > table[x].reference && x!=page_num){
            lowest= table[x].reference;
            index=x;
        }
    }
    return index;
}
u_int32_t updateRef(){
    return referenceBit++;
}

u_int32_t currentRef(){
    return referenceBit;
}