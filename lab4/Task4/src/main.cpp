#include <Arduino.h>

#include "Relay.h"
#include "L298N.h"
#include "SerialMap.h"

#include "config.h"

Relay relay(RELAY_IN);
L298N motor(MOTOR_IN1, MOTOR_IN2, MOTOR_EN);

String inputBuffer;

void setup(){
    stdinToSerial();
    redirectStdout();
}

void loop(){
}
