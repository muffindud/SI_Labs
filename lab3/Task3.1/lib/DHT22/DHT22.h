#ifndef DHT22_H
#define DHT22_H

#include <Arduino.h>

class DHT22{
    private:
        int pin;
    public:
        DHT22(int pin);
        void setup();
};

#endif