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

LedTaskSelector taskSelector;

LedTaskExcuter taskExecuter;

SerialIO serialIO;

TaskScheduler taskScheduler;

void scanTaskSelector(){
    if(blackButton.getButtonPressed()){
        return;
    }

    if(taskSelector.getActive()){
        taskScheduler.addTaskToQueue(&scanTaskSelector, HIGH_PRIORITY, false);
        printf("Task Selector Active: %d\n\r", taskSelector.getActive());
    }

    return;
}

void scanBlackButton(){
    blackButton.scanButtonState();

    if(blackButton.getButtonPressed()){
        taskSelector.toggleActive();

        if(taskSelector.getActive()){
            taskScheduler.addTaskToQueue(&scanTaskSelector, HIGH_PRIORITY, false);
        }
    }

    return;
}

void scanRedButton(){
    redButton.scanButtonState();
    return;
}

void scanGreenButton(){
    greenButton.scanButtonState();
    return;
}

void addTasks(){
    taskScheduler.addTasks();
    return;
}

void setup(){
    redLed.setup();
    greenLed.setup();

    blackButton.setup();
    redButton.setup();
    greenButton.setup();

    serialIO.setup();

    taskScheduler.addTaskToQueue(&scanBlackButton, VERY_HIGH_PRIORITY, true);
    taskScheduler.addTaskToQueue(&scanRedButton, VERY_HIGH_PRIORITY, true);
    taskScheduler.addTaskToQueue(&scanTaskSelector, MEDIUM_PRIORITY, true);
    taskScheduler.addTaskToQueue(&scanGreenButton, VERY_HIGH_PRIORITY, true);
    taskScheduler.addTaskToQueue(&addTasks, VERY_LOW_PRIORITY, true);

    taskScheduler.addTasks();
}

void loop(){
    taskScheduler.executeTask();
}

//TODO: Redo LedTaskExcuter
//TODO: Redo LedTaskSelector
