#ifndef LED_TASK_SELECTOR_H
#define LED_TASK_SELECTOR_H

#include <Arduino.h>

#include "Led.h"

class LedTaskSelector{
    private:
        Led *selectorLed;

        bool active = false;
    public:
        LedTaskSelector(Led *selectorLed);

        void toggleActive();
        void setActive(bool active);
        bool getActive();
};

#endif
