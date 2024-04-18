#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <Arduino.h>
#include <Encoder.h>

class Speedometer {
    private:
        Encoder encoder;
    public:
        Speedometer(Encoder encoder);
};

#endif