#include "Button.h"

Button::Button(int pin){
    buttonPin = pin;
    pinMode(buttonPin, INPUT);
}

void Button::scanButtonState(){
    lastButtonState = buttonState;
    buttonState = digitalRead(buttonPin);
    changedState = buttonState != lastButtonState;
    return;
}

bool Button::getButtonPressed(){
    return changedState && buttonState;
}

bool Button::getButtonDown(){
    return buttonState;
}

bool Button::getButtonUp(){
    return changedState && !buttonState;
}

