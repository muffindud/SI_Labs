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

    #if DEBUG
        printf("NTC Thermistor reading: %d\n\r", reading);
        printf("NTC Thermistor voltage: %d\n\r", (int)voltage);
        printf("NTC Thermistor resistance: %d\n\r", (int)resistance);
    #endif

    return temperature;
}
