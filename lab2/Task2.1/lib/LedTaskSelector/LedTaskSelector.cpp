#include "LedTaskSelector.h"

LedTaskSelector::LedTaskSelector(Led &led, Button &button): outputLed(led), selectorButton(button){}

void LedTaskSelector::scanTaskSelector(){
    if(selectorButton.getButtonPressed()){
        outputLed.togglePowerState();
        active = outputLed.getPowerState();
    }
}
