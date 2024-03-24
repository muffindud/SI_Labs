#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

#define GAMMA 0.7
#define RL10 50

#include <Arduino.h>

#include "Convertor.h"
#include "../../src/config.h"

class Photoresistor{
    private:
        int pin;
    public:
        Photoresistor(int pin);
        void setup();

        int getReading();
        float getVoltage();
        float getResistance();
        float getLux();

        float readData();
};

#endif