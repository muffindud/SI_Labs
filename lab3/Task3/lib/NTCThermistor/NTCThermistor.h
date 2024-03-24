#ifndef NTC_THERMISTOR_H
#define NTC_THERMISTOR_H

#include <Arduino.h>

#include "Convertor.h"
#include "../../src/config.h"

class NTCThermistor{
    private:
        int pin;
    public:
        NTCThermistor(int pin);
        void setup();
        float readData();
};

#endif