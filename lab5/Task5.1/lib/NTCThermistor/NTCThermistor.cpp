#include "NTCThermistor.h"

NTCThermistor::NTCThermistor(int pin){
    this->pin = pin;
}

void NTCThermistor::setup(){
    pinMode(this->pin, INPUT);
}

int NTCThermistor::getReading(){
    return analogRead(this->pin);
}
