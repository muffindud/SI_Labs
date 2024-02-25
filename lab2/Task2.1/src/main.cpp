#define RED_LED 13
#define GREEN_LED 12

#define BLACK_BUTTON 11
#define RED_BUTTON 10
#define GREEN_BUTTON 9

#include <Arduino.h>

#include "Led.h"
#include "Button.h"
#include "SerialIO.h"
#include "LedTaskSelector.h"
#include "LedTaskExcuter.h"

Led redLed(RED_LED);
Led greenLed(GREEN_LED);

Button blackButton(BLACK_BUTTON);
Button redButton(RED_BUTTON);
Button greenButton(GREEN_BUTTON);

LedTaskSelector taskSelector(
    redLed, 
    blackButton
);

LedTaskExcuter taskExecuter(
    taskSelector, 
    greenLed, 
    redButton, 
    greenButton
);

SerialIO serialIO;

void setup(){
    redLed.setup();
    greenLed.setup();

    blackButton.setup();
    redButton.setup();
    greenButton.setup();

    serialIO.setup();
}

void loop(){
    blackButton.scanButtonState();
    redButton.scanButtonState();
    greenButton.scanButtonState();

    taskSelector.scanTaskSelector();
    taskExecuter.scanTaskExcuter();
}
