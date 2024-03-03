#include "LedTaskExcuter.h"

LedTaskExcuter::LedTaskExcuter(){}

void LedTaskExcuter::increaseFrequency(){
    ledDelay -= DELAY_STEP;

    if(ledDelay < MIN_DELAY){
        ledDelay = MIN_DELAY;
    }

    return;
}

void LedTaskExcuter::decreaseFrequency(){
    ledDelay += DELAY_STEP;

    if(ledDelay > MAX_DELAY){
        ledDelay = MAX_DELAY;
    }

    return;
}

int LedTaskExcuter::getDelay(){
    return ledDelay;
}
