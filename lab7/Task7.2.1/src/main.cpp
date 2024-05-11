#define SERIAL_BAUD 115200
#define RX_PIN 16
#define TX_PIN 17

#include <Arduino.h>

void setup(){
    Serial.begin(SERIAL_BAUD);
    Serial1.begin(SERIAL_BAUD, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop(){
    Serial.print(Serial1.read());
    delay(1000);
}
