#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button{
    private:
        int buttonPin;
        bool lastButtonState = false;
        bool buttonState = false;
        bool changedState = false;

    public:
        Button(int pin);

        void scanButtonState();
        bool getButtonPressed();
        bool getButtonDown();
        bool getButtonUp();
};

#endif
