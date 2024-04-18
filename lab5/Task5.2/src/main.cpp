#include <Arduino.h>
#include <Encoder.h>

#include "L298N.h"

#include "config.h"

#if !TINKERCAD
    #include "SerialMap.h"
#endif

L298N motor(MOTOR_ENA, MOTOR_IN1, MOTOR_IN2);
Encoder encoder(ENCODER_A, ENCODER_B);

void setup(){
    #if TINKERCAD
        Serial.begin(SERIAL_BAUD);
    #else
        redirectSTDOUT();
        redirectSTDIN();
    #endif
}

void loop(){
    motor.setSpeed();

    #if TINKERCAD
        Serial.print("Speed: ");
        Serial.println(motor.getSpeed());
    #else
        printf("Speed: %d\n", motor.getSpeed());
    #endif
}
