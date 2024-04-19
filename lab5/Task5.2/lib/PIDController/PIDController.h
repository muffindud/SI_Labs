#ifndef PID_CONROLLER_H
#define PID_CONROLLER_H

#include <Arduino.h>
#include <Encoder.h>

class PIDController {
    private:
        Encoder encoder;
    public:
        PIDController(Encoder encoder);
};

#endif