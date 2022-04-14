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
        entry[x].reference=-1;
    }

    return entry;
}    
void printValidTable(pageEntry * table){

    for(int x=0;x<32;x++){
        if(table[x].valid==1){
            printf("Index:\t %d ------Frame:\t %d ---- Reference:\t%d\n",x,table[x].frameNumber,table[x].reference);
        }
    }



}
u_int32_t lowestRef(pageEntry * table,u_int32_t length,u_int32_t page_num){


    int index=0;
    int lowest=0;
    for(int x=0;x<length;x++){
        //finds lowest and prevents replacing itself
        if(table[x].valid==1){
            if(lowest==0){
                lowest = table[x].reference;
                index=x;
                }

            else if(table[x].reference < lowest){
                lowest = table[x].reference;
                index=x;

            }
        }


        
    }
    printf("Oldest index is %d\n",index);
    printf("Oldest frame is %d\n",table[index].frameNumber);
        printf("Oldest ref  is %d\n",table[index].reference);



    return index;
}
u_int32_t updateRef(){
    return referenceBit++;
}

u_int32_t currentRef(){
    return referenceBit;
}