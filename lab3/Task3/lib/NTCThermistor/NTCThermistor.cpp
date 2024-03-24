#include "NTCThermistor.h"

NTCThermistor::NTCThermistor(int pin){
    this->pin = pin;
}

void NTCThermistor::setup(){
    pinMode(this->pin, INPUT);
}

float NTCThermistor::readData(){
    int reading = analogRead(this->pin);
    float voltage = reading * 5.0 / 1023.0;
    float resistance = 10000.0 * voltage / (5.0 - voltage);
    float temperature = 1.0 / (1.0 / 298.15 + 1.0 / 3950.0 * log(resistance / 10000.0)) - 273.15;

    return temperature;
}
