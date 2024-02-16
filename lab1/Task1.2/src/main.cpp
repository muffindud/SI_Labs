#define GREEN_LED_PIN 12
#define RED_LED_PIN 13

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

// #define KEYPAD_ROW_1 11
// #define KEYPAD_ROW_2 10
// #define KEYPAD_ROW_3 9
// #define KEYPAD_ROW_4 8

// #define KEYPAD_COL_1 5
// #define KEYPAD_COL_2 4
// #define KEYPAD_COL_3 3
// #define KEYPAD_COL_4 2

#include <Arduino.h>

#include "SerialIO.h"
#include "Keypad.h"

char keyMap[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins[KEYPAD_ROWS] = {11, 10, 9, 8};
byte colPins[KEYPAD_COLS] = {5, 4, 3, 2};

SerialIO serialIO;
Keypad keyPad = Keypad(
    makeKeymap(keyMap),
    rowPins,
    colPins,
    KEYPAD_ROWS,
    KEYPAD_COLS
);
Led greenLed = Led(GREEN_LED_PIN);

String password = "";

void setup(){
    serialIO.setup();
    greenLed.setup();
    greenLed.setPowerState(false);
    serialIO.serialDisplay("Enter password: ");
}

void loop(){
    serialIO.serialDisplay(String(keyPad.getKey()));

    // if(key != NO_KEY){
    //     serialIO.serialDisplay("*");
    //     greenLed.togglePowerState();
    // }
}
