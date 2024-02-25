#include "LedTaskSelector.h"

LedTaskSelector::LedTaskSelector(Led &led, Button &button): 
    selectorLed(led), 
    selectorButton(button)
{}

void LedTaskSelector::scanTaskSelector(){
    if(selectorButton.getButtonPressed()){
        selectorLed.togglePowerState();
        active = selectorLed.getPowerState();
    }
}

bool LedTaskSelector::getActive(){
    return active;
}
