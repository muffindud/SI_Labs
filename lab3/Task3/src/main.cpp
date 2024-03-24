// Analog to voltage: https://docs.arduino.cc/built-in-examples/basics/ReadAnalogVoltage/
// Photoresistor (voltage to resistance to lux): https://docs.wokwi.com/parts/wokwi-photoresistor-sensor
// Thermistor (voltage to resistance to temperature): https://docs.wokwi.com/parts/wokwi-ntc-temperature-sensor

#define NTC_THERMISTOR_PIN A3
#define PHOTORESISTOR_PIN A2

// Built-in libraries
#include <Arduino.h>

// Custom libraries
#include "SerialIO.h"
#include "NTCThermistor.h"
#include "Photoresistor.h"
#include "Convertor.h"

SerialIO serialIO;
NTCThermistor ntcThermistor(NTC_THERMISTOR_PIN);
Photoresistor photoresistor(PHOTORESISTOR_PIN);

long int temperatureReadings[READINGS_SIZE];
float spTemperature;
float vaTemperature;

long int lightReadings[READINGS_SIZE];
float spLight;
float vaLight;

void setup();
void loop();
void getTemperatureReading();
void getLightReading();
void computeSPTemperature();
void computeSPLight();
void computeVATemperature();
void computeVALight();
void getInitialReadings();

void getTemperatureReading(){
    for(int i = 0; i < READINGS_SIZE - 1; i++){
        temperatureReadings[i] = temperatureReadings[i + 1];
    }

    temperatureReadings[READINGS_SIZE - 1] = ntcThermistor.getReading();
}

void getLightReading(){
    for(int i = 0; i < READINGS_SIZE - 1; i++){
        lightReadings[i] = lightReadings[i + 1];
    }

    lightReadings[READINGS_SIZE - 1] = photoresistor.getReading();
}

void computeSPTemperature(){
    long int spTemperatureReadings[SALT_PEPER_SIZE];

    for(int i = WEIGHTS_SIZE - SALT_PEPER_SIZE; i < SALT_PEPER_SIZE; i++){
        spTemperatureReadings[i] = temperatureReadings[i];
    }

    spTemperature = toTemperature(toResistance(toVoltage(saltPeperFilter(spTemperatureReadings))));
}

void computeSPLight(){
    long int spLightReadings[SALT_PEPER_SIZE];

    for(int i = WEIGHTS_SIZE - SALT_PEPER_SIZE; i < SALT_PEPER_SIZE; i++){
        spLightReadings[i] = lightReadings[i];
    }

    spLight = toLux(toResistance(toVoltage(saltPeperFilter(spLightReadings))));
}

void computeVATemperature(){
    long int vaTemperatureReadings[WEIGHTS_SIZE];

    for(int i = WEIGHTS_SIZE - WEIGHTS_SIZE; i < WEIGHTS_SIZE; i++){
        vaTemperatureReadings[i] = temperatureReadings[i];
    }

    vaTemperature = toTemperature(toResistance(toVoltage(weightedAverage(vaTemperatureReadings))));
}

void computeVALight(){
    long int vaLightReadings[WEIGHTS_SIZE];

    for(int i = WEIGHTS_SIZE - WEIGHTS_SIZE; i < WEIGHTS_SIZE; i++){
        vaLightReadings[i] = lightReadings[i];
    }

    vaLight = toLux(toResistance(toVoltage(weightedAverage(vaLightReadings))));
}

void setup(){
    serialIO.setup();
    ntcThermistor.setup();
    photoresistor.setup();

    for(int i = 0; i < READINGS_SIZE; i++){
        temperatureReadings[i] = ntcThermistor.getReading();
        lightReadings[i] = photoresistor.getReading();
    }
}

void loop(){
    getTemperatureReading();
    computeSPTemperature();
    computeVATemperature();
    
    getLightReading();
    computeSPLight();
    computeVALight();

    printf("Temperature: SP: %ld, VA: %ld\n\r", (long int)spTemperature, (long int)vaTemperature);
    printf("Light: SP: %ld, VA: %ld\n\r", (long int)spLight, (long int)vaLight);

    delay(100);
}
