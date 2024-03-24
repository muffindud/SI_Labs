#define NTC_THERMISTOR_PIN A3
#define DHT22_PIN 2

// Built-in libraries
#include <Arduino.h>

// Custom libraries
#include "SerialIO.h"
#include "DHT22.h"
#include "NTCThermistor.h"

SerialIO serialIO;
DHT22 dht22(DHT22_PIN);
NTCThermistor ntcThermistor(NTC_THERMISTOR_PIN);

void setup();
void loop();

// Initial setup function
void setup(){
    serialIO.setup();
    dht22.setup();
    ntcThermistor.setup();
}

void loop(){}
