#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#define POTENTIOMETER_MIN_VALUE 0
#define POTENTIOMETER_MAX_VALUE 1023

#include <Arduino.h>

class Potentiometer{
    private:
        int pin;
        int value;
    public:
        Potentiometer(int pin);
        int getValue();
};

#endif