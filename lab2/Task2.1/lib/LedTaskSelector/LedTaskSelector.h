#ifndef LED_TASK_SELECTOR_H
#define LED_TASK_SELECTOR_H

#include <Arduino.h>

class LedTaskSelector{
    private:
        bool active = false;

    public:
        LedTaskSelector();

        void toggleActive();
        void setActive(bool active);
        bool getActive();
};

#endif
