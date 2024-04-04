#ifndef L298N_H
#define L298N_H

#define SPEED_STEP 1

#include <Arduino.h>

class L298N{
    private:
        int in1;
        int in2;
        int en;

        /*
            Speed of the motor in %.
            range: -100 to 100
        */
        int speed = 0;

        /*
            Map the speed to the analogWrite range.
            range: -100 to 100
        */
        int analogMap(int speed);
    public:
        L298N(int in1, int in2, int en);

        /*
            Set the speed of the motor in %.
            Intended for use in a loop for gradual speed change.
            range: -100 to 100
        */
        void setSpeed(int speed);

        /*
            Get the speed of the motor in %.
            range: -100 to 100
        */
        int getSpeed();
};

#endif