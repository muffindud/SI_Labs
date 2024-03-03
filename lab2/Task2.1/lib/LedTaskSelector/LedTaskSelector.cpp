#include "LedTaskSelector.h"

LedTaskSelector::LedTaskSelector(Led *selectorLed):
    selectorLed(selectorLed)
{}

void LedTaskSelector::toggleActive(){
    active = !active;
    selectorLed->setPowerState(active);

    return;
}

void LedTaskSelector::setActive(bool active){
    this->active = active;
    selectorLed->setPowerState(active);

    return;
}

bool LedTaskSelector::getActive(){
    return active;
}
