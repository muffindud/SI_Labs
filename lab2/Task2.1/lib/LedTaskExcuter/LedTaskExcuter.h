#ifndef LED_TASK_EXCUTER_H
#define LED_TASK_EXCUTER_H

#include <Arduino.h>

#include "LedTaskSelector.h"
#include "Led.h"
#include "SerialIO.h"

class LedTaskExcuter{
    private:
        LedTaskSelector &taskSelector;
        Led &outputLed;
        Button &frequencyDecreaseButton;
        Button &frequencyIncreaseButton;

        int delayTime = 500;

        const int MIN_DELAY_TIME = 50;
        const int MAX_DELAY_TIME = 1000;
        const int DELAY_TIME_STEP = 50;

    public:
        LedTaskExcuter(
            LedTaskSelector &selector, 
            Led &led, 
            Button &decreaseButton, 
            Button &increaseButton
        );

        void scanTaskExcuter();
        void increaseFrequency();
        void decreaseFrequency();

        int getDelayTime();
};

#endif
