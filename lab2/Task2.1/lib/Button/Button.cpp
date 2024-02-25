#include "Button.h"

Button::Button(int pin){
    buttonPin = pin;
}

void Button::setup(){
    pinMode(buttonPin, INPUT);
}

void Button::scanButtonState(){
    lastButtonState = buttonState;
    buttonState = digitalRead(buttonPin);
    changedState = buttonState != lastButtonState;
    delay(10);
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

