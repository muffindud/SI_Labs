#include "Convertor.h"

float toVoltage(int reading){
    return reading / 1023.0 * 5;
}

float toResistance(float voltage){
    return 10000 * voltage / (5 - voltage);
}

long int saltPeperFilter(long int data[SALT_PEPER_SIZE]){
    for(int i = 0; i < SALT_PEPER_SIZE; i++){
        for(int j = i + 1; j < SALT_PEPER_SIZE; j++){
            if(data[i] > data[j]){
                int temp = data[i];

                data[i] = data[j];
                data[j] = temp;
            }
        }
    }

    return data[(int)(SALT_PEPER_SIZE / 2)];
}

float weightedAverage(long int data[WEIGHTS_SIZE]){
    float sum = 0;

    for(int i = 0; i < WEIGHTS_SIZE; i++){
        sum += data[i] * WEIGHTS[i];
    }

    return sum;
}

float toTemperature(float resistance){
    return 1.0 / (1.0 / 298.15 + 1.0 / 3950.0 * log(resistance / 10000.0)) - 273.15;
}

float toLux(float resistance){
    return pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, 1 / GAMMA);
}
