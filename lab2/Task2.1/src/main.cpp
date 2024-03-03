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
#include "Task.h"
#include "TaskScheduler.h"

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

TaskScheduler taskScheduler;

void scanBlackButton(){
    printf("Scanning black button\n\r");
    blackButton.scanButtonState();
    return;
}

void scanRedButton(){
    printf("Scanning red button\n\r");
    redButton.scanButtonState();
    return;
}

void scanGreenButton(){
    printf("Scanning green button\n\r");
    greenButton.scanButtonState();
    return;
}

void scanTaskSelector(){
    printf("Scanning task selector\n\r");
    taskSelector.scanTaskSelector();
    return;
}

void setup(){
    redLed.setup();
    greenLed.setup();

    blackButton.setup();
    redButton.setup();
    greenButton.setup();

    serialIO.setup();

    taskScheduler.addTask(&scanBlackButton, VERY_HIGH_PRIORITY, true);
    taskScheduler.addTask(&scanRedButton, VERY_HIGH_PRIORITY, true);
    taskScheduler.addTask(&scanTaskSelector, MEDIUM_PRIORITY, true);
    taskScheduler.addTask(&scanGreenButton, VERY_HIGH_PRIORITY, true);
}

void loop(){
    taskScheduler.executeTask();
}

//TODO: Redo LedTaskExcuter
//TODO: Redo LedTaskSelector
