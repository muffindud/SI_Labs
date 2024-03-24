#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

#define GAMMA 0.7
#define RL10 50

#include <Arduino.h>

#include "../../src/config.h"

class Photoresistor{
    private:
        int pin;
    public:
        Photoresistor(int pin);
        void setup();
        float readData();
};

#endif