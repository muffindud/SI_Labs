#ifndef NTC_THERMISTOR_H
#define NTC_THERMISTOR_H

#define BETA 3950

#include <Arduino.h>

class NTCThermistor{
    private:
        int pin;
    public:
        NTCThermistor(int pin);
        int getReading();
        int getCelsius();
};

#endif