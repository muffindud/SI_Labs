#ifndef CONVERTOR_H
#define CONVERTOR_H

#define SALT_PEPER_SIZE 5

float toVoltage(int reading);
float toResistance(float voltage);
int saltPeperFilter(int data[SALT_PEPER_SIZE]);

#endif