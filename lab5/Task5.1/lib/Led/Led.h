#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led{
    private:
        int ledPin;
        bool powerState;
    public:
        Led(int pin);

        void setPowerState(bool state);
        bool getPowerState();

        void togglePowerState();
};

#endif
