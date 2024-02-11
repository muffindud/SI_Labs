#ifndef SERIALOUT_H
#define SERIALOUT_H

#define SERIALOUT_PROMPT '>'

#include <Arduino.h>
#include <stdio.h>

#include "SerialIn.h"

class SerialOut{
    private:
        SerialIn serialIn;

        char command_prompt = SERIALOUT_PROMPT;
    public:
        SerialOut();

        void setSerialIn(SerialIn serialIn);

        void serialDisplay(String message);
};

#endif