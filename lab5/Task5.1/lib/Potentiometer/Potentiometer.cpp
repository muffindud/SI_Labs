#include "Potentiometer.h"

Potentiometer::Potentiometer(int pin){
    this->pin = pin;
    pinMode(pin, INPUT);
}

int Potentiometer::getValue(){
    return analogRead(pin);
}
