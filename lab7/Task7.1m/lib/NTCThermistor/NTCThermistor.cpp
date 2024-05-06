#include "NTCThermistor.h"

NTCThermistor::NTCThermistor(int pin, int analogResolution){
    this->pin = pin;
    this->analogResolution = analogResolution;
    pinMode(this->pin, INPUT);
}

int NTCThermistor::getReading(){
    return analogRead(this->pin);
}

int NTCThermistor::getCelsius(){
    return 1 / (log(1 / ((pow(2, analogResolution)) / this->getReading() - 1)) / BETA + 1.0 / 298.15) - 273.15;
}
