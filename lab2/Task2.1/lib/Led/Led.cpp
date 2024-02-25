#include "Led.h"

Led::Led(int pin){
    ledPin = pin;
}

void Led::setup(){
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, !powerState);
}

void Led::setPowerState(bool state){
    powerState = state;
    digitalWrite(ledPin, !powerState);
}

bool Led::getPowerState(){
    return powerState;
}

void Led::togglePowerState(){
    powerState = !powerState;
    digitalWrite(ledPin, !powerState);
}
