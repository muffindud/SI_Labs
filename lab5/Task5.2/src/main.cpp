#include <Arduino.h>
#include <Encoder.h>

#include "L298N.h"
#include "PIDController.h"

#include "config.h"

L298N motor(MOTOR_ENA, MOTOR_IN1, MOTOR_IN2);
Encoder encoder(ENCODER_A, ENCODER_B);

PIDController pid(&encoder, &motor);

void setup(){
    Serial.begin(SERIAL_BAUD);
    pid.setDesiredSpeed(4200);
}

void loop(){
    pid.update();
}
