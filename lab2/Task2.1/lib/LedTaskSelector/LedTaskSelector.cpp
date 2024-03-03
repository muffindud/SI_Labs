#include "LedTaskSelector.h"

LedTaskSelector::LedTaskSelector(){}

void LedTaskSelector::toggleActive(){
    active = !active;
    return;
}

void LedTaskSelector::setActive(bool active){
    this->active = active;
    return;
}

bool LedTaskSelector::getActive(){
    return active;
}
