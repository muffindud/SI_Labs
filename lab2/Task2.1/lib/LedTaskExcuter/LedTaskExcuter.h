#ifndef LED_TASK_EXCUTER_H
#define LED_TASK_EXCUTER_H

#define MIN_DELAY (unsigned long)100
#define MAX_DELAY (unsigned long)1000
#define DELAY_STEP (unsigned long)50

#define START_DELAY (unsigned long)500

#include <Arduino.h>

class LedTaskExcuter{
    private:
        unsigned long ledDelay = START_DELAY;
        unsigned long startTime = 0;
        unsigned long passedTime = 0;

    public:
        LedTaskExcuter();

        void increaseFrequency();
        void decreaseFrequency();

        void startTimer();
        void snapTime();
        unsigned long getPassedTime();

        unsigned long getDelay();
};

#endif
