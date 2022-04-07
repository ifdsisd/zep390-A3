#include <stdlib.h>
#include <sys/types.h>
#include "pagetable.h"
#include "phypage.h"
#include <stdio.h>

int main(int argc,char * argv[]){

    pageEntry * pageTable = initialize();
    u_int32_t * addresses;


    enterAddress(pageTable,address);
  
  
    free(pageTable);



    return 0;
}