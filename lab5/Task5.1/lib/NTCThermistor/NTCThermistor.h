#ifndef NTC_THERMISTOR_H
#define NTC_THERMISTOR_H

#include <Arduino.h>

#include "Convertor.h"

class NTCThermistor{
    private:
        int pin;
    public:
        NTCThermistor(int pin);
        void setup();
        int getReading();
};

#endif