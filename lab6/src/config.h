#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#ifndef __AVR_ATmega328P__
const int GREEN_1_PIN = PA1;
const int YELLOW_1_PIN = PA2;
const int RED_1_PIN = PA3;

const int GREEN_2_PIN = PB1;
const int YELLOW_2_PIN = PB10;
const int RED_2_PIN = PB11;

const int BIN_0_PIN = PA12;
const int BIN_1_PIN = PA15;
const int BIN_2_PIN = PB3;
const int BIN_3_PIN = PB4;
const int BIN_4_PIN = PB5;
const int BIN_5_PIN = PB6;
const int BIN_6_PIN = PB7;
const int BIN_7_PIN = PB8;

const int BUTTON_0_PIN = PB15;
const int BUTTON_1_PIN = PA8;

#else
const int GREEN_1_PIN = 2;
const int YELLOW_1_PIN = 3;
const int RED_1_PIN = 4;
const int GREEN_2_PIN = 5;
const int YELLOW_2_PIN = 6;
const int RED_2_PIN = 7;
const int BIN_0_PIN = 8;
const int BIN_1_PIN = 9;
const int BIN_2_PIN = 10;
const int BIN_3_PIN = 11;
const int BIN_4_PIN = 12;
const int BIN_5_PIN = A0;
const int BIN_6_PIN = A1;
const int BIN_7_PIN = A2;

const int BUTTON_0_PIN = A3;
const int BUTTON_1_PIN = A4;
#endif

#endif