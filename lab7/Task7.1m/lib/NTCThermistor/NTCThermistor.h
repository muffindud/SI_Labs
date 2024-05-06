#ifndef NTC_THERMISTOR_H
#define NTC_THERMISTOR_H

#define ANALOG_RESOLUTION 12
#define BETA 3950

#include <Arduino.h>

class NTCThermistor{
    private:
        int pin;
        int analogResolution;
    public:
        NTCThermistor(int pin, int analogResolution = 10);
        int getReading();
        int getCelsius();
};

#endif