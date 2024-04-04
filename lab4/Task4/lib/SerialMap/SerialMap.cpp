#include "SerialMap.h"

LCD *lcd = NULL;

int lcdRow = 0;
int lcdCol = 0;

FILE *_stdin;
FILE *_stdout;

bool serialEnabled = false;
bool serialPrint = false;

static int getCharSerial(__attribute__((unused)) FILE *stream){
    while(!Serial.available());
    return Serial.read();
}

static int putChar(char c, __attribute__((unused)) FILE *stream){
    int ret;

    if(serialPrint){
        if(c == 127){
            Serial.write(8);
            ret = Serial.write(' ');
            Serial.write(8);
        }else if(c == 13){
            ret = Serial.write(c);
            Serial.write(10);
        }
        else{ 
            ret = Serial.write(c);
        }
    }else{
        if(c == 13){
            lcdCol = 0;
            lcdRow++;
            if(lcdRow >= LCD_ROWS){
                lcdRow = 0;
            }
            ret = 1;
        }else if(c == 127){
            lcdCol--;
            if(lcdCol < 0){
                lcdCol = 0;
            }
            lcd->setCursor(lcdCol, lcdRow);
            ret = lcd->print(' ');
            lcd->setCursor(lcdCol, lcdRow);
        }else{
            lcd->setCursor(lcdCol, lcdRow);
            ret = lcd->print(c);
            lcdCol++;
            if(lcdCol >= LCD_COLS){
                lcdCol = 0;
                lcdRow++;
                if(lcdRow >= LCD_ROWS){
                    lcdRow = 0;
                }
            }
        }
    }

    return ret == 1 ? 0 : -1;
}

void redirectStdout(){
    if(lcd == NULL){
        lcd = new LCD(LCD_ADDR, LCD_COLS, LCD_ROWS);
        lcd->begin();
    }

    if(!serialEnabled){
        Serial.begin(SERIAL_BAUD);
        serialEnabled = true;
    }

    _stdout = fdevopen(&putChar, NULL);
}

void stdoutToSerial(){
    serialPrint = true;
}

void stdoutToLCD(){
    serialPrint = false;
}

void stdinToSerial(){
    if(!serialEnabled)
        Serial.begin(SERIAL_BAUD);
    
    serialEnabled = true;

    _stdin = fdevopen(NULL, &getCharSerial);
}
