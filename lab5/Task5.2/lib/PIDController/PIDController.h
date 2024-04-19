#ifndef PID_CONROLLER_H
#define PID_CONROLLER_H

#define TOLERANCE 10

#include <Arduino.h>
#include <Encoder.h>
#include "L298N.h"

enum comparison{
    EQUAL,
    GREATER,
    LESS
};

class PIDController {
    private:
        Encoder encoder;
        L298N motor;

        float kp = 0.1;
        int vDesired = 0;
    public:
        /*
            * Constructor
            * @param encoder: encoder object
            * @param motor: motor object
        */
        PIDController(Encoder encoder, L298N motor);

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
};

/*
    * Compare two integers with tolerance
    * @param a: first integer
    * @param b: second integer
    * @param tolerance: tolerance
    * @return: true if a and b are within tolerance, false otherwise
*/
comparison closeCompare(int a, int b, int tolerance);

#endif