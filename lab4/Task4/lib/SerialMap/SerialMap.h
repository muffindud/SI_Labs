#ifndef SEIAL_MAP_H
#define SEIAL_MAP_H

#define SERIAL_BAUD 9600

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

#include <Arduino.h>
#include <stdio.h>
#include "LCD.h"

/*
    Redirect stdout (default to LCD).
*/
void redirectStdout();

/*
    Map the standard output to the serial port.
*/ 
void stdoutToSerial();

/*
    Map the standard output to the LCD.
*/
void stdoutToLCD();

/*
    Map the standard input to the serial port.
*/
void stdinToSerial();

/*
    Clear the LCD.
*/
void clearLCD();

#endif