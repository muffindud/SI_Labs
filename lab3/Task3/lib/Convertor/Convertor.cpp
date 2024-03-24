#include "Convertor.h"

float toVoltage(int reading){
    return reading / 1023.0 * 5;
}

float toResistance(float voltage){
    return 10000 * voltage / (5 - voltage);
}

int saltPeperFilter(int data[SALT_PEPER_SIZE]){
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
