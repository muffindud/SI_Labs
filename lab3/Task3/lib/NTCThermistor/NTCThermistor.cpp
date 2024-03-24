#include "NTCThermistor.h"

NTCThermistor::NTCThermistor(int pin){
    this->pin = pin;
}

void NTCThermistor::setup(){
    pinMode(this->pin, INPUT);
}

float NTCThermistor::readData(){
    int reading = analogRead(this->pin);
    Serial.print("Reading: ");
    Serial.println(reading);
    float voltage = reading * 5.0 / 1023.0;
    Serial.print("Voltage: ");
    Serial.println(voltage);
    float resistance = 10000.0 * voltage / (5.0 - voltage);
    Serial.print("Resistance: ");
    Serial.println(resistance);
    float temperature = 1.0 / (1.0 / 298.15 + 1.0 / 3950.0 * log(resistance / 10000.0)) - 273.15;

    return temperature;
}
