#define THERMISTOR_PIN 33
#define ANALOG_RESOLUTION 12

#define SERIAL_BAUD 115200
#define RX_PIN 16
#define TX_PIN 17

#include <Arduino.h>
#include "NTCThermistor.h"

NTCThermistor thermistor(THERMISTOR_PIN, ANALOG_RESOLUTION);

void setup(){
    Serial.begin(SERIAL_BAUD);
    Serial1.begin(SERIAL_BAUD, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop(){
    int temperature = thermistor.getCelsius();
    Serial1.write(temperature);
    Serial.println(temperature);
    delay(1000);
}
