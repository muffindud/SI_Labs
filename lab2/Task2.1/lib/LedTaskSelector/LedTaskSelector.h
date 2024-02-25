#ifndef LED_TASK_SELECTOR_H
#define LED_TASK_SELECTOR_H

#include <Arduino.h>

#include "Led.h"
#include "Button.h"

class LedTaskSelector{
    private:
        Led &outputLed;
        Button &selectorButton;
        
        bool active = false;

    public:
        LedTaskSelector(Led &led, Button &button);

        void scanTaskSelector();
};

#endif
