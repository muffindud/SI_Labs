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
    // TODO: Adapt to FreeRTOS

    return;
}

void scanTaskSelector(){
    // TODO: Adapt to FreeRTOS

    return;
}

void scanBlackButton(){
    blackButton.scanButtonState();

    // TODO: Adapt to FreeRTOS

    return;
}

void scanRedButton(){
    redButton.scanButtonState();

    // TODO: Adapt to FreeRTOS

    return;
}

void scanGreenButton(){
    greenButton.scanButtonState();

    // TODO: Adapt to FreeRTOS

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

}

void loop(){
}
