#define THERMISTOR_PIN 33
#define ANALOG_RESOLUTION 12
#define SELF_ADDRESS 0x70

#include <Arduino.h>
#include <Wire.h>

#include "NTCThermistor.h"

NTCThermistor thermistor(THERMISTOR_PIN, ANALOG_RESOLUTION);

void setup(){
    Wire.begin(SELF_ADDRESS);

    Wire.onRequest([](){
        int temperature = thermistor.getCelsius();
        Wire.write(temperature);
    });
}

void loop(){
}
