#include "LedTaskExcuter.h"

LedTaskExcuter::LedTaskExcuter(
    LedTaskSelector &selector, 
    Led &led, 
    Button &decreaseButton, 
    Button &increaseButton
): 
    taskSelector(selector), 
    outputLed(led), 
    frequencyDecreaseButton(decreaseButton), 
    frequencyIncreaseButton(increaseButton)
{}

void LedTaskExcuter::increaseFrequency(){
    if(frequencyIncreaseButton.getButtonPressed() && delayTime > MIN_DELAY_TIME){
        delayTime -= DELAY_TIME_STEP;
    }
}

void LedTaskExcuter::decreaseFrequency(){
    if(frequencyDecreaseButton.getButtonPressed() && delayTime < MAX_DELAY_TIME){
        delayTime += DELAY_TIME_STEP;
    }
}

void LedTaskExcuter::scanTaskExcuter(){
    if(taskSelector.getActive()){
        
    }
    else{
        outputLed.togglePowerState();
        delay(delayTime);
    }

    increaseFrequency();
    decreaseFrequency();
}

int LedTaskExcuter::getDelayTime(){
    return delayTime;
}
