// #define RED_LED 13
// #define GREEN_LED 12

// #define BLACK_BUTTON 11
// #define RED_BUTTON 10
// #define GREEN_BUTTON 9

#include <Arduino.h>

// #include "Led.h"
// #include "Button.h"
#include "SerialIO.h"
// #include "LedTaskSelector.h"
// #include "LedTaskExcuter.h"
#include "Task.h"
#include "TaskScheduler.h"

// Led redLed(RED_LED);
// Led greenLed(GREEN_LED);

// Button blackButton(BLACK_BUTTON);
// Button redButton(RED_BUTTON);
// Button greenButton(GREEN_BUTTON);

// LedTaskSelector taskSelector(
//     redLed, 
//     blackButton
// );

// LedTaskExcuter taskExecuter(
//     taskSelector, 
//     greenLed, 
//     redButton, 
//     greenButton
// );

SerialIO serialIO;

void tempTask(){
    // delay(100);
    delayMicroseconds(100);
    // printf("Temp task executed\n");
    return;
}

Task task(VERY_HIGH_PRIORITY, tempTask, true);
TaskScheduler taskScheduler(&task);

void setup(){
    // redLed.setup();
    // greenLed.setup();

    // blackButton.setup();
    // redButton.setup();
    // greenButton.setup();

    serialIO.setup();
    taskScheduler.executeTasks();
}

void loop(){
    // blackButton.scanButtonState();
    // redButton.scanButtonState();
    // greenButton.scanButtonState();

    // taskSelector.scanTaskSelector();
    // taskExecuter.scanTaskExcuter();

    // taskScheduler.executeTasks();
    // printf("Loop executed\n\r");
}
