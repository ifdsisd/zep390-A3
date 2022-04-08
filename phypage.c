#include "phypage.h"

//OS is 0 so plus 1
int frameCounter=1;


int currentFrame(){
    return frameCounter;
}

int nextFrame(){

        return frameCounter++;

}