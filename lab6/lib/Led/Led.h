#ifndef LED_H
#define LED_H

#define LED_MIN_PWM 0
#define LED_MAX_PWM 255

#include <Arduino.h>

class Led{
    private:
        int ledPin;
        bool powerState = false;
    public:
        Led(int pin);

        void setPowerState(bool state);
        void setPWM(int value);
        bool getPowerState();

        void togglePowerState();
};

#endif
