#define TASK_DELAY_MS 100

#define TASK_DELAY_TICKS 0

#define BLACK_BUTTON_DELAY_OFFSET_TICKS 0
#define RED_BUTTON_DELAY_OFFSET_TICKS 1
#define GREEN_BUTTON_DELAY_OFFSET_TICK 2
#define TASK_EXECUTER_DELAY_OFFSET_TICKS 3

#define RED_LED 13
#define GREEN_LED 12

#define BLACK_BUTTON 11
#define RED_BUTTON 10
#define GREEN_BUTTON 9

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

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

LedTaskSelector taskSelector(&redLed);

LedTaskExcuter taskExecuter;

SerialIO serialIO;

TaskHandle_t blackButtonHandler = NULL;
TaskHandle_t redButtonHandler = NULL;
TaskHandle_t greenButtonHandler = NULL;
TaskHandle_t taskExecuterHandler = NULL;
TaskHandle_t greenLedFrequencyHandler = NULL;

void scanTaskExecuter(void *pvParameters);
void scanBlackButton(void *pvParameters);
void scanRedButton(void *pvParameters);
void scanGreenButton(void *pvParameters);
void secretTask();
void scanSequence();
void setup();
void loop();

// Dependent task
void scanTaskExecuter(void *pvParameters){
    (void) pvParameters;
    TickType_t xLastWakeTime;

    vTaskDelay(TASK_DELAY_TICKS + TASK_EXECUTER_DELAY_OFFSET_TICKS);

    xLastWakeTime = xTaskGetTickCount();
    for(;;){
        greenLed.togglePowerState();

        vTaskDelayUntil(&xLastWakeTime, taskExecuter.getDelay() / portTICK_PERIOD_MS);
    }
}

// Permanent task
void scanBlackButton(void *pvParameters){
    (void) pvParameters;
    TickType_t xLastWakeTime;

    vTaskDelay(TASK_DELAY_TICKS + BLACK_BUTTON_DELAY_OFFSET_TICKS);

    xLastWakeTime = xTaskGetTickCount();
    for(;;){
        blackButton.scanButtonState();

        if(blackButton.getButtonPressed()){
            taskSelector.toggleActive();

            if(taskSelector.getActive()){
                if(taskExecuterHandler != NULL){
                    vTaskDelete(taskExecuterHandler);
                    taskExecuterHandler = NULL;
                }

                // printf("Task Selector: active\n\r");
            }else{
                xTaskCreate(
                    scanTaskExecuter,
                    "Scan Task Executer",
                    128,
                    NULL,
                    3,
                    &taskExecuterHandler
                );

                // printf("Task Selector: inactive\n\r");
            }
        }

        vTaskDelayUntil(&xLastWakeTime, TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
}

// Permanent task
void scanRedButton(void *pvParameters){
    (void) pvParameters;
    TickType_t xLastWakeTime;

    vTaskDelay(TASK_DELAY_TICKS + RED_BUTTON_DELAY_OFFSET_TICKS);

    xLastWakeTime = xTaskGetTickCount();
    for(;;){
        redButton.scanButtonState();

        if(redButton.getButtonPressed()){
            taskExecuter.decreaseFrequency();
            printf("Delay: %ld (+%ld)\n\r", taskExecuter.getDelay(), DELAY_STEP);
        }

        vTaskDelayUntil(&xLastWakeTime, TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
}

// Permanent task
void scanGreenButton(void *pvParameters){
    (void) pvParameters;
    TickType_t xLastWakeTime;

    vTaskDelay(TASK_DELAY_TICKS + GREEN_BUTTON_DELAY_OFFSET_TICK);

    xLastWakeTime = xTaskGetTickCount();
    for(;;){
        greenButton.scanButtonState();

        if(greenButton.getButtonPressed()){
            taskExecuter.increaseFrequency();
            printf("Delay: %ld (-%ld)\n\r", taskExecuter.getDelay(), DELAY_STEP);
        }

        vTaskDelayUntil(&xLastWakeTime, TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
}

// Permanent task (TODO)
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
        // TODO: Adapt to FreeRTOS
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

    taskSelector.toggleActive();

    xTaskCreate(
        scanBlackButton,
        "Read Black Button State",
        128,
        NULL,
        3,
        &blackButtonHandler
    );

    xTaskCreate(
        scanRedButton,
        "Read Red Button State",
        128,
        NULL,
        3,
        &redButtonHandler
    );

    xTaskCreate(
        scanGreenButton,
        "Read Green Button State",
        128,
        NULL,
        3,
        &greenButtonHandler
    );

    vTaskStartScheduler();
}

void loop(){}

// TODO: Implement proper delaying
