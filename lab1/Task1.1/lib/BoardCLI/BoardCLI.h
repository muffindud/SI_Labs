#ifndef BOARDCLI_H
#define BOARDCLI_H

#include "Led.h"

#include <Arduino.h>

class BoardCLI{
    private:
        Led led;

        char input;
        String command_buffer = "";
        
        char command_prompt = '>';

        String on_command = "led on";
        String off_command = "led off";

        String new_line = "\n\r";
        String backspace = "\b \b";

        String on_response = "Turning on the LED." + new_line;
        String off_response = "Turning off the LED." + new_line;
        String invalid_command = "Invalid command: ";

        String command;
    public:
        BoardCLI(Led diode);

        void setup();
        void getCommand();
};

#endif