#include "Convertor.h"

float toVoltage(int reading){
    return reading / 1023.0 * 5;
}

float toResistance(float voltage){
    return 10000 * voltage / (5 - voltage);
}
