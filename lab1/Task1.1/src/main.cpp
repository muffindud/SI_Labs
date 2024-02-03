#define LED_PIN 13

#include <stdio.h>
#include <Arduino.h>

#include "Led.h"
#include "BoardCLI.h"

Led led(LED_PIN);
BoardCLI boardCLI(led);

void setup() {
    led.setup();
    boardCLI.setup();
}

void loop() {
    boardCLI.getCommand();
}
