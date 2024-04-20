#ifndef L298N_H
#define L298N_H

#define SPEED_STEP 1

#include <Arduino.h>

class L298N{
    private:
        int in1;
        int in2;
        int en;

        int speed = 0;
        int targetSpeed = 0;

        int analogMap(int speed);
    public:
        L298N(int in1, int in2, int en);

        /*
            * Set the target speed of the motor in %.
            * @param speed: speed in % [-100; 100].
        */
        void setSpeed(int speed);

        /*
            Get the speed of the motor in %.
            @ return: speed in % [-100; 100].
        */
        int getSpeed();

        /*
            Get the target speed of the motor in %.
            @ return: target speed in % [-100; 100].
        */
        int getTargetSpeed();
};

#endif