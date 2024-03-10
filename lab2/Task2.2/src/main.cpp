#define TASK_DELAY_MS 100
#define SECRET_TASK_BLINK_PERIOD_MS 500

#define TASK_DELAY_TICKS 0

#define BLACK_BUTTON_DELAY_OFFSET_TICKS 0
#define RED_BUTTON_DELAY_OFFSET_TICKS 10
#define GREEN_BUTTON_DELAY_OFFSET_TICK 20
#define SECRET_SEQUENCE_OFFSET_TICKS 30
#define TASK_EXECUTER_DELAY_OFFSET_TICKS 40

#define RED_LED 13
#define GREEN_LED 12

#define BLACK_BUTTON 11
#define RED_BUTTON 10
#define GREEN_BUTTON 9

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

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

SemaphoreHandle_t xSemaphore = NULL;

void scanTaskExecuter(void *pvParameters);
void scanBlackButton(void *pvParameters);
void scanRedButton(void *pvParameters);
void scanGreenButton(void *pvParameters);
void scanSequence();
void secretTask();
void setup();
void loop();

void scanTaskExecuter(void *pvParameters){
    (void) pvParameters;
    TickType_t xLastWakeTime;

    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    vTaskDelay(TASK_DELAY_TICKS + TASK_EXECUTER_DELAY_OFFSET_TICKS);
    xSemaphoreGive(xSemaphore);

    xLastWakeTime = xTaskGetTickCount();
    for(;;){
        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        greenLed.togglePowerState();
        xSemaphoreGive(xSemaphore);

        vTaskDelayUntil(&xLastWakeTime, taskExecuter.getDelay() / portTICK_PERIOD_MS);
    }
}

void scanBlackButton(void *pvParameters){
    (void) pvParameters;
    TickType_t xLastWakeTime;

    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    vTaskDelay(TASK_DELAY_TICKS + BLACK_BUTTON_DELAY_OFFSET_TICKS);
    xSemaphoreGive(xSemaphore);

    xLastWakeTime = xTaskGetTickCount();
    for(;;){
        blackButton.scanButtonState();

        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        if(blackButton.getButtonPressed()){
            taskSelector.toggleActive();

            if(taskSelector.getActive()){
                if(taskExecuterHandler != NULL){
                    vTaskDelete(taskExecuterHandler);
                    taskExecuterHandler = NULL;
                }
            }else{
                xTaskCreate(
                    scanTaskExecuter,
                    "Scan Task Executer",
                    128,
                    NULL,
                    3,
                    &taskExecuterHandler
                );
            }

            scanSequence();
        }
        xSemaphoreGive(xSemaphore);

        vTaskDelayUntil(&xLastWakeTime, TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
}

void scanRedButton(void *pvParameters){
    (void) pvParameters;
    TickType_t xLastWakeTime;

    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    vTaskDelay(TASK_DELAY_TICKS + RED_BUTTON_DELAY_OFFSET_TICKS);
    xSemaphoreGive(xSemaphore);

    xLastWakeTime = xTaskGetTickCount();
    for(;;){
        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        redButton.scanButtonState();

        if(redButton.getButtonPressed()){
            taskExecuter.decreaseFrequency();
            printf("Delay: %ld (+%ld)\n\r", taskExecuter.getDelay(), DELAY_STEP);
        
            scanSequence();
        }
        xSemaphoreGive(xSemaphore);

        vTaskDelayUntil(&xLastWakeTime, TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
}

void scanGreenButton(void *pvParameters){
    (void) pvParameters;
    TickType_t xLastWakeTime;

    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    vTaskDelay(TASK_DELAY_TICKS + GREEN_BUTTON_DELAY_OFFSET_TICK);
    xSemaphoreGive(xSemaphore);

    xLastWakeTime = xTaskGetTickCount();
    for(;;){
        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        greenButton.scanButtonState();

        if(greenButton.getButtonPressed()){
            taskExecuter.increaseFrequency();
            printf("Delay: %ld (-%ld)\n\r", taskExecuter.getDelay(), DELAY_STEP);

            scanSequence();
        }
        xSemaphoreGive(xSemaphore);

        vTaskDelayUntil(&xLastWakeTime, TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
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
        secretTask();
    }
}

void secretTask(){
    // Save the last state of the LEDs
    bool lastGreenLedState = greenLed.getPowerState();
    bool lastRedLedState = redLed.getPowerState();

    printf("Secret task started\n\r");
    // ================ Secret task starts here =======================
    greenLed.setPowerState(false);
    redLed.setPowerState(true);

    // Alternate the LEDs 10 times with a delay of 500ms
    for(int i = 0; i < 10; i++){
        greenLed.togglePowerState();
        redLed.togglePowerState();
        vTaskDelay(SECRET_TASK_BLINK_PERIOD_MS / portTICK_PERIOD_MS);
    }
    // ================ Secret task ends here =========================
    printf("Secret task ended\n\r");

    // Restore the last state of the LEDs
    greenLed.setPowerState(lastGreenLedState);
    redLed.setPowerState(lastRedLedState);
}

void setup(){
    redLed.setup();
    greenLed.setup();

    blackButton.setup();
    redButton.setup();
    greenButton.setup();

    serialIO.setup();

    taskSelector.toggleActive();

    xSemaphore = xSemaphoreCreateMutex();

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
