#ifndef PID_CONROLLER_H
#define PID_CONROLLER_H

#define MAX_SPEED_PER_SECOND 5400 
#define PERIOD_UPDATE_MS 1000
#define KP 0.3
#define KI 0
#define KD 0

#include <Arduino.h>
#include <Encoder.h>
#include "L298N.h"


class PIDController {
    private:
        Encoder *encoder;
        L298N *motor;

        int vDesired = 0;

        float kp = KP;
        float ki = KI;
        float kd = KD;

        int encoderValue;
    public:

        /*
            * Constructor
            * @param encoder: encoder object
            * @param motor: motor object
        */
        PIDController(Encoder *encoder, L298N *motor);

        /*
            * Call PID controller update and set motor speed
            * Call this function in loop
            * @return: void
        */
        void update();

        /*
            * Set desired speed
            * @param speed: desired speed
            * @return: void
        */
        void setDesiredSpeed(int speed);

        /*
            * Get encoder value
            * @return: encoder value
        */
        int getEncoderValue();
};

#endif