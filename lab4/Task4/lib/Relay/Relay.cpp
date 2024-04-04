#include "Relay.h"

Relay::Relay(int pin){
    this->pin = pin;
    this->state = false;
    pinMode(this->pin, OUTPUT);
}

void Relay::toggle(){
    this->state = !this->state;
    digitalWrite(this->pin, this->state);
}

void Relay::setState(bool state){
    this->state = state;
    digitalWrite(this->pin, this->state);
}

bool Relay::getState(){
    return this->state;
}
