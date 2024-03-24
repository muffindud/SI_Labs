#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

#include <Arduino.h>

#include "Convertor.h"

class Photoresistor{
    private:
        int pin;
    public:
        Photoresistor(int pin);
        void setup();
        int getReading();
};

#endif