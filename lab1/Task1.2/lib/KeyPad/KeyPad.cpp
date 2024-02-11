#include "KeyPad.h"

KeyPad::KeyPad(int rowPins[KEYPAD_ROWS], int colPins[KEYPAD_COLS]){
    for(int i = 0; i < KEYPAD_ROWS; i++){
        this->rowPins[i] = rowPins[i];
    }

    for(int i = 0; i < KEYPAD_COLS; i++){
        this->colPins[i] = colPins[i];
    }

    for(int i = 0; i < KEYPAD_ROWS; i++){
        pinMode(this->rowPins[i], INPUT);
    }

    for(int i = 0; i < KEYPAD_COLS; i++){
        pinMode(this->colPins[i], OUTPUT);
        digitalWrite(this->colPins[i], HIGH);
    }
}

bool KeyPad::loopState(){
}
