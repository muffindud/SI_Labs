#define GREEN_LED_PIN 12
#define RED_LED_PIN 13

#include <stdio.h>
#include <Arduino.h>

#include "Led.h"
#include "BoardCLI.h"

Led greenLed(GREEN_LED_PIN);
Led redLed(RED_LED_PIN);

void setup() {
    greenLed.setup();
    redLed.setup();
}

void loop() {

}
