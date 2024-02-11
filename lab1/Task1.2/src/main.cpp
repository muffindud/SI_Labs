#define GREEN_LED_PIN 12
#define RED_LED_PIN 13

#define KEYPAD_ROW_1 11
#define KEYPAD_ROW_2 10
#define KEYPAD_ROW_3 9
#define KEYPAD_ROW_4 8

#define KEYPAD_COL_1 5
#define KEYPAD_COL_2 4
#define KEYPAD_COL_3 3
#define KEYPAD_COL_4 2

#include <Arduino.h>

#include "SerialIO.h"


SerialIO serialIO;

void setup(){
    serialIO.setup();
}

void loop(){
    serialIO.waitInput();
}
