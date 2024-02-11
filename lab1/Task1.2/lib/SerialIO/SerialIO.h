#ifndef SERIALIO_H
#define SERIALIO_H

#include "Led.h"

#include <Arduino.h>
#include <stdio.h>

class SerialIO{
    private:
        char input;
        String command_buffer = "";
        
        char command_prompt = '>';

        String new_line = "\n\r";
        String backspace = "\b \b";

    public:
        SerialIO();

        void setup();
        void waitInput();
        void serialDisplay(String message);
        void handleBackspace();
        void printNewLine();
        void handleCommand();
        void clearCommandBuffer();
        String getCommand();
};

#endif