#define THERMISTOR_PIN 33
#define SERIAL_BAUD 115200
#define ANALOG_RESOLUTION 12

#include <Arduino.h>
#include <Wire.h>

#include "NTCThermistor.h"

NTCThermistor thermistor(THERMISTOR_PIN, ANALOG_RESOLUTION);

void setup(){
    Serial.begin(SERIAL_BAUD);
}

void loop(){
    Serial.println(thermistor.getCelsius());
    delay(1000);
}
