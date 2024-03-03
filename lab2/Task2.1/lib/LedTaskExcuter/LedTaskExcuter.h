#ifndef LED_TASK_EXCUTER_H
#define LED_TASK_EXCUTER_H

#define MIN_DELAY 100
#define MAX_DELAY 1000
#define DELAY_STEP 50

#define START_DELAY 500

#include <Arduino.h>

class LedTaskExcuter{
    private:
        int ledDelay = START_DELAY;

    public:
        LedTaskExcuter();

        void increaseFrequency();
        void decreaseFrequency();

        int getDelay();
};

#endif
