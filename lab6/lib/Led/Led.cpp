#include "Led.h"

Led::Led(int pin){
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, powerState);
}

void Led::setPowerState(bool state){
    powerState = state;
    digitalWrite(ledPin, powerState);
}

void Led::setPWM(int value){
    analogWrite(ledPin, value);
}

bool Led::getPowerState(){
    return powerState;
}

void Led::togglePowerState(){
    powerState = !powerState;
    digitalWrite(ledPin, powerState);
}
