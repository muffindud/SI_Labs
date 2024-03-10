// Delay for each task
#define TASK_DELAY_MS 100

// Secret task blink period in ms
#define SECRET_TASK_BLINK_PERIOD_MS 500

// Initial delay offset for each task
#define TASK_DELAY_TICKS 0

// Delay offset for each task
#define BLACK_BUTTON_DELAY_OFFSET_TICKS 0
#define RED_BUTTON_DELAY_OFFSET_TICKS 1
#define GREEN_BUTTON_DELAY_OFFSET_TICK 2
#define SECRET_SEQUENCE_OFFSET_TICKS 3
#define TASK_EXECUTER_DELAY_OFFSET_TICKS 4

// Pins for components
#define RED_LED 13
#define GREEN_LED 12
#define BLACK_BUTTON 11
#define RED_BUTTON 10
#define GREEN_BUTTON 9

// Built-in libraries
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// Custom libraries
#include "Led.h"
#include "Button.h"
#include "SerialIO.h"
#include "LedTaskSelector.h"
#include "LedTaskExcuter.h"

// Component objects
Led redLed(RED_LED);
Led greenLed(GREEN_LED);
Button blackButton(BLACK_BUTTON);
Button redButton(RED_BUTTON);
Button greenButton(GREEN_BUTTON);
SerialIO serialIO;

// Task objects
LedTaskSelector taskSelector(&redLed);
LedTaskExcuter taskExecuter;

// Task handlers
TaskHandle_t blackButtonHandler = NULL;
TaskHandle_t redButtonHandler = NULL;
TaskHandle_t greenButtonHandler = NULL;

TaskHandle_t taskExecuterHandler = NULL;

// Semaphore handler
// SemaphoreHandle_t xSemaphore = NULL;
SemaphoreHandle_t greenLedSemaphore = NULL;
SemaphoreHandle_t frequencySemaphore = NULL;

// Function prototypes
void scanTaskExecuter(void *pvParameters);
void scanBlackButton(void *pvParameters);
void scanRedButton(void *pvParameters);
void scanGreenButton(void *pvParameters);
void scanSequence();
void secretTask();
void setup();
void loop();

// Blink task function
void scanTaskExecuter(void *pvParameters){
    (void) pvParameters;
    TickType_t xLastWakeTime;

    // Create task with delay offset
    vTaskDelay(TASK_DELAY_TICKS + TASK_EXECUTER_DELAY_OFFSET_TICKS);

    xLastWakeTime = xTaskGetTickCount();
    for(;;){
        xSemaphoreTake(greenLedSemaphore, portMAX_DELAY);
        
        // Toggle the green led state every delay period
        greenLed.togglePowerState();
        
        xSemaphoreGive(greenLedSemaphore);

        vTaskDelayUntil(&xLastWakeTime, taskExecuter.getDelay() / portTICK_PERIOD_MS);
    }
}

// Black button scan task functions
void scanBlackButton(void *pvParameters){
    (void) pvParameters;
    TickType_t xLastWakeTime;

    // Create task with delay offset
    vTaskDelay(TASK_DELAY_TICKS + BLACK_BUTTON_DELAY_OFFSET_TICKS);

    // Task loop
    xLastWakeTime = xTaskGetTickCount();
    for(;;){
        // Scan the button state
        blackButton.scanButtonState();

        if(blackButton.getButtonPressed()){
            // Toggle the task executer state
            taskSelector.toggleActive();

            if(taskSelector.getActive()){
                printf("Task Executer active\n\r");

                // If the task selector is active, delete the task executer
                if(taskExecuterHandler != NULL){
                    vTaskDelete(taskExecuterHandler);
                    taskExecuterHandler = NULL;
                }
            }else{
                printf("Task Executer inactive\n\r");

                // If the task selector is inactive, create the task executer
                xTaskCreate(
                    scanTaskExecuter,
                    "Scan Task Executer",
                    128,
                    NULL,
                    3,
                    &taskExecuterHandler
                );
            }

            // Scan the secret sequence
            scanSequence();
        }

        vTaskDelayUntil(&xLastWakeTime, TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
}

// Red button scan task functions
void scanRedButton(void *pvParameters){
    (void) pvParameters;
    TickType_t xLastWakeTime;

    // Create task with delay offset
    vTaskDelay(TASK_DELAY_TICKS + RED_BUTTON_DELAY_OFFSET_TICKS);

    // Task loop
    xLastWakeTime = xTaskGetTickCount();
    for(;;){
        // Scan the button state
        redButton.scanButtonState();

        if(redButton.getButtonPressed()){
            xSemaphoreTake(frequencySemaphore, portMAX_DELAY);

            // Increase the frequency of the task executer
            taskExecuter.decreaseFrequency();
            printf("Delay: %ld (+%ld)\n\r", taskExecuter.getDelay(), DELAY_STEP);
            
            xSemaphoreGive(frequencySemaphore);

            // Scan the secret sequence
            scanSequence();
        }

        vTaskDelayUntil(&xLastWakeTime, TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
}

// Green button scan task functions
void scanGreenButton(void *pvParameters){
    (void) pvParameters;
    TickType_t xLastWakeTime;

    // Create task with delay offset
    vTaskDelay(TASK_DELAY_TICKS + GREEN_BUTTON_DELAY_OFFSET_TICK);

    // Task loop
    xLastWakeTime = xTaskGetTickCount();
    for(;;){
        // Scan the button state
        greenButton.scanButtonState();

        if(greenButton.getButtonPressed()){
            xSemaphoreTake(frequencySemaphore, portMAX_DELAY);

            // Decrease the frequency of the task executer
            taskExecuter.increaseFrequency();
            printf("Delay: %ld (-%ld)\n\r", taskExecuter.getDelay(), DELAY_STEP);

            xSemaphoreGive(frequencySemaphore);

            // Scan the secret sequence
            scanSequence();
        }

        vTaskDelayUntil(&xLastWakeTime, TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
}

// Secret sequence scan function
int sequenceIndex = 0;
char secretSequence[] = {'B', 'B', 'G', 'R', 'R', 'G'};
void scanSequence(){
    // Scan if the secret sequence is pressed in order
    // If the sequence is pressed in order, call the secret task
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

    // If the sequence is not pressed in order, reset the sequence index
    if(sequenceIndex == 6){
        sequenceIndex = 0;
        secretTask();
    }
}

// Secret task function
void secretTask(){
    // Save the last state of the LEDs
    xSemaphoreTake(greenLedSemaphore, portMAX_DELAY);
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
    xSemaphoreGive(greenLedSemaphore);
}

// Initial setup function
void setup(){
    // Initialize the components
    redLed.setup();
    greenLed.setup();
    blackButton.setup();
    redButton.setup();
    greenButton.setup();
    serialIO.setup();

    // Initialize the task selector to on state
    taskSelector.toggleActive();

    // Create semaphore mutex
    greenLedSemaphore = xSemaphoreCreateMutex();
    frequencySemaphore = xSemaphoreCreateMutex();

    // Create initial high priority task
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

    // Start the scheduler
    vTaskStartScheduler();
}

void loop(){}
