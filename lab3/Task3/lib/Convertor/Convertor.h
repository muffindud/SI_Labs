#ifndef CONVERTOR_H
#define CONVERTOR_H

#define GAMMA 0.7
#define RL10 50

#define SALT_PEPER_SIZE 5

#define WEIGHTS (float[]){0.5, 0.25, 0.15, 0.1}
#define WEIGHTS_SIZE 4

#if SALT_PEPER_SIZE > WEIGHTS_SIZE
    #define READINGS_SIZE SALT_PEPER_SIZE
#else
    #define READINGS_SIZE WEIGHTS_SIZE
#endif

#include <Arduino.h>

float toVoltage(int reading);
float toResistance(float voltage);

long int saltPeperFilter(long int data[SALT_PEPER_SIZE]);
float weightedAverage(long int data[WEIGHTS_SIZE]);

float toTemperature(float resistance);
float toLux(float resistance);

#endif