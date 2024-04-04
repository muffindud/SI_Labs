#ifndef SEIAL_MAP_H
#define SEIAL_MAP_H

#define SERIAL_BAUD 9600

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

#include <Arduino.h>
#include <stdio.h>
#include "LCD.h"

void stdoutToSerial();
void stdinToSerial();
void stdoutToLCD();

#endif