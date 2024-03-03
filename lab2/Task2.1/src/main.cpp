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

LedTaskSelector taskSelector(&redLed);

LedTaskExcuter taskExecuter;

SerialIO serialIO;

TaskScheduler taskScheduler;

void taskReset(){
    taskScheduler.taskReset();
    return;
}

void increaseGreenLedFrequency(){
    taskExecuter.increaseFrequency();
    printf("Delay: %ld (-%ld)\n\r", taskExecuter.getDelay(), DELAY_STEP);
    return;
}

void decreaseGreenLedFrequency(){
    taskExecuter.decreaseFrequency();
    printf("Delay: %ld (+%ld)\n\r", taskExecuter.getDelay(), DELAY_STEP);
    return;
}

void scanTaskExecuter(){
    if(!taskSelector.getActive()){
        taskScheduler.addTaskToQueue(&scanTaskExecuter, MEDIUM_PRIORITY, false);

        taskExecuter.snapTime();
        if(taskExecuter.getPassedTime() > taskExecuter.getDelay()){
            greenLed.togglePowerState();
            taskExecuter.startTimer();
        }
    }

    return;
}

void scanTaskSelector(){
    if(taskSelector.getActive()){
        taskScheduler.addTaskToQueue(&scanTaskSelector, MEDIUM_PRIORITY, false);
    }

    return;
}

void scanBlackButton(){
    blackButton.scanButtonState();

    if(blackButton.getButtonPressed()){
        taskSelector.toggleActive();

        if(taskSelector.getActive()){
            taskScheduler.addTaskToQueue(&scanTaskSelector, MEDIUM_PRIORITY, false);
            printf("TaskSelector active\n\r");
        }else{
            taskScheduler.addTaskToQueue(&scanTaskExecuter, MEDIUM_PRIORITY, false);
            taskExecuter.startTimer();
            printf("TaskSelector inactive\n\r");
        }
    }

    return;
}

void scanRedButton(){
    redButton.scanButtonState();

    if(redButton.getButtonPressed()){
        taskScheduler.addTaskToQueue(&decreaseGreenLedFrequency, HIGH_PRIORITY, false);
    }
    return;
}

void scanGreenButton(){
    greenButton.scanButtonState();

    if(greenButton.getButtonPressed()){
        taskScheduler.addTaskToQueue(&increaseGreenLedFrequency, HIGH_PRIORITY, false);
    }

    return;
}

void secretTask(){
    bool lastGreenLedState = greenLed.getPowerState();
    bool lastRedLedState = redLed.getPowerState();

    greenLed.setPowerState(false);
    redLed.setPowerState(true);

    for(int i = 0; i < 10; i++){
        greenLed.togglePowerState();
        redLed.togglePowerState();
        delay(500);
    }

    greenLed.setPowerState(lastGreenLedState);
    redLed.setPowerState(lastRedLedState);

    return;
}

int sequenceIndex = 0;
char secretSequence[] = {'B', 'B', 'G', 'R', 'R', 'G'};
void scanSequence(){
    if(secretSequence[sequenceIndex] == 'B' && sequenceIndex < 6){
        if(blackButton.getButtonPressed()){
            sequenceIndex++;
        }else if(greenButton.getButtonPressed() || redButton.getButtonPressed()){
            sequenceIndex = 0;
        }
    }else if(secretSequence[sequenceIndex] == 'R' && sequenceIndex < 6){
        if(redButton.getButtonPressed()){
            sequenceIndex++;
        }else if(greenButton.getButtonPressed() || blackButton.getButtonPressed()){
            sequenceIndex = 0;
        }
    }else if(secretSequence[sequenceIndex] == 'G' && sequenceIndex < 6){
        if(greenButton.getButtonPressed()){
            sequenceIndex++;
        }else if(redButton.getButtonPressed() || blackButton.getButtonPressed()){
            sequenceIndex = 0;
        }
    }

    if(sequenceIndex == 6){
        sequenceIndex = 0;
        taskScheduler.addTaskToQueue(&secretTask, HIGH_PRIORITY, false);
    }

    return;
}

void setup(){
    redLed.setup();
    greenLed.setup();

    blackButton.setup();
    redButton.setup();
    greenButton.setup();

    serialIO.setup();

    taskScheduler.addTaskToQueue(&taskReset, VERY_HIGH_PRIORITY, true);
    taskScheduler.taskReset();

    taskScheduler.addTaskToQueue(&scanBlackButton, HIGH_PRIORITY, true);
    taskScheduler.addTaskToQueue(&scanRedButton, HIGH_PRIORITY, true);
    taskScheduler.addTaskToQueue(&scanGreenButton, HIGH_PRIORITY, true);

    taskScheduler.addTaskToQueue(&scanSequence, MEDIUM_PRIORITY, true);

    taskSelector.toggleActive();
    taskScheduler.addTaskToQueue(&scanTaskSelector, MEDIUM_PRIORITY, false);
}

void loop(){
    taskScheduler.executeTask();
}
