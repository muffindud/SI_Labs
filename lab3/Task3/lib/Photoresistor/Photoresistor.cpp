#include "Photoresistor.h"

Photoresistor::Photoresistor(int pin){
    this->pin = pin;
}

void Photoresistor::setup(){
    pinMode(this->pin, INPUT);
}

float Photoresistor::readData(){
    int reading = getReading();
    float voltage = getVoltage();
    float resistance = getResistance();
    float lux = getLux();

    #if DEBUG
        printf("Photoresistor reading: %d\n\r", reading);
        printf("Photoresistor voltage: %d\n\r", (int)voltage);
        printf("Photoresistor resistance: %d\n\r", (int)resistance);
    #endif

    return lux;
}

int Photoresistor::getReading(){
    return analogRead(this->pin);
}

float Photoresistor::getVoltage(){
    return toVoltage(this->getReading());
}

float Photoresistor::getResistance(){
    return toResistance(this->getVoltage());
}

float Photoresistor::getLux(){
    return pow(RL10 * 1e3 * pow(10, GAMMA) / this->getResistance(), 1 / GAMMA);
}
