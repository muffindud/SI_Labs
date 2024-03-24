#define NTC_THERMISTOR_PIN A3
#define PHOTORESISTOR_PIN A2

// Built-in libraries
#include <Arduino.h>

// Custom libraries
#include "SerialIO.h"
#include "NTCThermistor.h"
#include "Photoresistor.h"

SerialIO serialIO;
NTCThermistor ntcThermistor(NTC_THERMISTOR_PIN);
Photoresistor photoresistor(PHOTORESISTOR_PIN);

void setup();
void loop();

// Initial setup function
void setup(){
    serialIO.setup();
    ntcThermistor.setup();
    photoresistor.setup();
}

void loop(){
    printf("\n\r");

    printf("====================================\n\r");
    float temperature = ntcThermistor.readData();
    printf("Temperature: %d\n\r", (int)temperature);

    printf("------------------------------------\n\r");
    
    float light = photoresistor.readData();
    printf("Light: %d\n\r", (int)light);
    printf("====================================\n\r");


    delay(1000);
}
