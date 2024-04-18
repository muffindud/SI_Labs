#ifndef SEIAL_MAP_H
#define SEIAL_MAP_H

#define SERIAL_BAUD 9600

#include <Arduino.h>
#include <stdio.h>

/*
    Redirect stdout (default to LCD).
*/
void redirectSTDOUT();

/*
    Map the standard input to the serial port.
*/
void redirectSTDIN();


#endif