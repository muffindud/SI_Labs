#include "Photoresistor.h"

Photoresistor::Photoresistor(int pin){
    this->pin = pin;
}

void Photoresistor::setup(){
    pinMode(this->pin, INPUT);
}

float Photoresistor::readData(){
    int reading = analogRead(this->pin);
    float voltage = reading / 1024. * 5;
    float resistance = 2000 * voltage / (1 - voltage / 5);
    float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, 1 / GAMMA);

    #if DEBUG
        printf("Photoresistor reading: %d\n\r", reading);
        printf("Photoresistor voltage: %d\n\r", (int)voltage);
        printf("Photoresistor resistance: %d\n\r", (int)resistance);
    #endif

    return lux;
}
