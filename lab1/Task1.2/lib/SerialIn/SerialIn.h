#ifndef SERIALIN_H
#define SERIALIN_H

#include <Arduino.h>
#include <stdio.h>

#include "SerialOut.h"

class SerialIn{
    private:
        SerialOut serialOut;

        String message;
        char input;
    public:
        SerialIn();

        void setSerialOut(SerialOut serialOut);

        void waitInput();
        void doCommand();

};

#endif