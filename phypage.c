#include "phypage.h"

//OS is 0 so plus 1
int frameCounter=1;


int Frame(){
    return frameCounter;
}

int nextFrame(){

    if (frameCounter++ == 8){
        frameCounter=RESET;
        return frameCounter;}
    else
        return frameCounter++;

}