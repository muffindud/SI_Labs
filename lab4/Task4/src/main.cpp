#define RELAY_IN 8
#define LCD_ADDR 0x27

#include <Arduino.h>
#include "Relay.h"
#include "SerialMap.h"

Relay relay(RELAY_IN);

void setup(){
    stdinToSerial();
    stdoutToLCD();
}

void loop(){

}
