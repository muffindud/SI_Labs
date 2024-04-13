#include <Arduino.h>
#include "config.h"
#include "LCD.h"
#include "NTCThermistor.h"
#include "Button.h"
#include "Led.h"

enum selector_t {
    HMIN,
    HMAX
};

Button plusButton(PLUS_BUTTON);
Button minusButton(MINUS_BUTTON);
Button x10Button(X10_BUTTON);
Button switchButton(SWITCH_BUTTON);

Led indicatorLed(INDICATOR_LED);

LCD lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

String inputBuffer = "";
selector_t selector = HMIN;

void setup(){

}

void loop(){
    
}
