#ifndef KEYPAD_H
#define KEYPAD_H

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#include <Arduino.h>

class KeyPad{
    private:
        int rowPins[KEYPAD_ROWS];
        int colPins[KEYPAD_COLS];

    public:
        KeyPad(int rowPins[KEYPAD_ROWS], int colPins[KEYPAD_COLS]);

        bool loopState();
};

#endif
