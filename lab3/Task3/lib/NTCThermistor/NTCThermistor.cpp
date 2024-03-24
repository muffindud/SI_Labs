#include "NTCThermistor.h"

NTCThermistor::NTCThermistor(int pin){
    this->pin = pin;
}

void NTCThermistor::setup(){
    pinMode(this->pin, INPUT);
}

float NTCThermistor::readData(){
    int reading = getReading();
    float voltage = getVoltage();
    float resistance = getResistance();
    float temperature = getTemperature();

    #if DEBUG
        printf("NTC Thermistor reading: %d\n\r", reading);
        printf("NTC Thermistor voltage: %d\n\r", (int)voltage);
        printf("NTC Thermistor resistance: %d\n\r", (int)resistance);
    #endif

    return temperature;
}

int NTCThermistor::getReading(){
    return analogRead(this->pin);
}

float NTCThermistor::getVoltage(){
    return toVoltage(this->getReading());
}

float NTCThermistor::getResistance(){
    return toResistance(this->getVoltage());
}

float NTCThermistor::getTemperature(){
    return 1.0 / (1.0 / 298.15 + 1.0 / 3950.0 * log(this->getResistance() / 10000.0)) - 273.15;
}
