#include "NTCThermistor.h"

NTCThermistor::NTCThermistor(int pin){
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

int NTCThermistor::getReading(){
    return analogRead(this->pin);
}

int NTCThermistor::getCelsius(){
    return 1 / (log(1 / (1023. / this->getReading() - 1)) / BETA + 1.0 / 298.15) - 273.15;
}
