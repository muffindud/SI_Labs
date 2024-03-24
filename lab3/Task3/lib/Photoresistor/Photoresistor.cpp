#include "Photoresistor.h"

Photoresistor::Photoresistor(int pin){
    this->pin = pin;
}

void Photoresistor::setup(){
    pinMode(this->pin, INPUT);
}

int Photoresistor::getReading(){
    return analogRead(this->pin);
}
