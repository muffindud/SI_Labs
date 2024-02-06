#define NEW_LINE 13
#define BACKSPACE 127

#include "BoardCLI.h"

BoardCLI::BoardCLI(Led diode): led(diode){} 

void BoardCLI::setup(){
    Serial.begin(9600);
    Serial.print(command_prompt);
}

void BoardCLI::getCommand(){
    if(Serial.available() > 0){
        input = Serial.read();
        Serial.print(input);

        if(input == NEW_LINE){
            if(command_buffer == on_command){
                Serial.println("Turning on the LED.");
                led.setPowerState(true);
            }
            else if(command_buffer == off_command){
                Serial.println("Turning off the LED.");
                led.setPowerState(false);
            }
            else{
                Serial.println(invalid_command);
            }

            command_buffer = "";
            Serial.print(command_prompt);
        }
        else if(input == BACKSPACE && command_buffer.length() > 0){
            command_buffer.remove(command_buffer.length() - 1);
            Serial.print("\b \b");
        }
        else if(input != BACKSPACE){
            command_buffer += input;
        }
    }
}
