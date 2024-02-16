#define GREEN_LED_PIN 12
#define RED_LED_PIN 13

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#include <Arduino.h>

#include "Keypad.h"
#include "Led.h"

char keyMap[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins[KEYPAD_ROWS] = {7, 6, 5, 4};
byte colPins[KEYPAD_COLS] = {3, 2, 1, 0};

Keypad keyPad = Keypad(
    makeKeymap(keyMap),
    rowPins,
    colPins,
    KEYPAD_ROWS,
    KEYPAD_COLS
);
Led greenLed = Led(GREEN_LED_PIN);
Led redLed = Led(RED_LED_PIN);

String password = "";

void setup(){
    greenLed.setup();
    redLed.setup();
}

void loop(){
    char key = keyPad.getKey();

    // Handle key presses
}
