#include "SerialMap.h"

FILE *_stdin;
FILE *_stdout;

bool serialEnabled = false;

static int getCharSerial(__attribute__((unused)) FILE *stream){
    if(Serial.available())
        return Serial.read();

    return -1;
}

static int putChar(char c, __attribute__((unused)) FILE *stream){
    int ret;

    if(c == 127){
        Serial.write(8);
        ret = Serial.write(' ');
        Serial.write(8);
    }else if(c == 10 || c == 13){
        ret = Serial.write(13) && Serial.write(10);
    }
    else{ 
        ret = Serial.write(c);
    }

    return ret == 1 ? 0 : -1;
}

void redirectSTDOUT(){
    if(!serialEnabled){
        Serial.begin(SERIAL_BAUD);
        serialEnabled = true;
    }

    _stdout = fdevopen(&putChar, NULL);
}

void redirectSTDIN(){
    if(!serialEnabled)
        Serial.begin(SERIAL_BAUD);
    
    serialEnabled = true;

    _stdin = fdevopen(NULL, &getCharSerial);
}
