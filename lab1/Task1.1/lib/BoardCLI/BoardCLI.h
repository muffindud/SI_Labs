#ifndef BOARDCLI_H
#define BOARDCLI_H

#include "Led.h"

#include <Arduino.h>

class BoardCLI{
    private:
        Led led;

        char input;
        String command_buffer = "";
        
        String command_prompt = ">";

        String on_command = "led on";
        String off_command = "led off";

        String invalid_command = "Invalid command: ";

        String command;
    public:
        BoardCLI(Led diode);

        void setup();
        void getCommand();
};

#endif