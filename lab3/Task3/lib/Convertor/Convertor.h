#ifndef CONVERTOR_H
#define CONVERTOR_H

#define SALT_PEPER_SIZE (int)5

#define WEIGHTS (float[]){0.5, 0.25, 0.15, 0.1}
#define WEIGHTS_SIZE (int)4

float toVoltage(int reading);
float toResistance(float voltage);

int saltPeperFilter(int data[SALT_PEPER_SIZE]);
float weightedAverage(int data[WEIGHTS_SIZE]);

#endif