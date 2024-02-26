#include "LedTaskSelector.h"

LedTaskSelector::LedTaskSelector(
    Led &led, 
    Button &button
): 
    selectorLed(led), 
    selectorButton(button)
{}

void LedTaskSelector::scanTaskSelector(){
    if(selectorButton.getButtonPressed()){
        selectorLed.togglePowerState();
        active = selectorLed.getPowerState();

        if(selectorLed.getPowerState()){
            printf("Selector LED: ON\n\r");
        }
        else{
            printf("Selector LED: OFF\n\r");
        }
    }
}

bool LedTaskSelector::getActive(){
    return active;
}
