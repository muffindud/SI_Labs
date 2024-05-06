#define SERIAL_BAUD 115200
#define SLAVE_ADDRESS 0x70

#include <Arduino.h>
#include <Wire.h>

void setup(){
    Wire.begin();
    Serial.begin(SERIAL_BAUD);
}

void loop(){
    uint8_t data = 0;
    Wire.requestFrom(SLAVE_ADDRESS, 2);
    if(Wire.available()){
        data = Wire.read();
        Serial.println(data);
    }
    delay(1000);
}
