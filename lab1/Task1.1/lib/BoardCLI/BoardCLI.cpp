#define NEW_LINE_1 13
#define NEW_LINE_2 10
#define BACKSPACE 8
#define SERIAL_BAUD_RATE 9600

#include "BoardCLI.h"

BoardCLI::BoardCLI(Led diode): led(diode){} 

void BoardCLI::setup(){
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.print(command_prompt);
}

void BoardCLI::getCommand(){
    if(Serial.available() > 0){
        input = Serial.read();

        if(input == NEW_LINE_1){
            Serial.println();

            if(command_buffer == on_command){
                Serial.println("Turning on the LED.");
                led.setPowerState(true);
            }
            else if(command_buffer == off_command){
                Serial.println("Turning off the LED.");
                led.setPowerState(false);
            }
            else{
                Serial.println(invalid_command + command_buffer);
            }

            command_buffer = "";
            Serial.print(command_prompt);
        }
        else if(input == BACKSPACE && command_buffer.length() > 0){
            command_buffer = command_buffer.substring(0, command_buffer.length() - 1);
            Serial.print("\b \b");
        }
        else if(input != BACKSPACE && input != NEW_LINE_1 && input != NEW_LINE_2){
            command_buffer += input;
            Serial.print(input);
        }
    }
}
