#include <Arduino.h>
#include "config.h"
#include "LCD.h"
#include "NTCThermistor.h"
#include "Button.h"
#include "Led.h"
#include "Relay.h"

enum selector_t {
    HMIN,
    HMAX
};

Button plusButton(PLUS_BUTTON);
Button minusButton(MINUS_BUTTON);
Button x10Button(X10_BUTTON);
Button switchButton(SWITCH_BUTTON);

Relay relay(RELAY_PIN);

LCD lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

NTCThermistor thermistor(THERMISTOR_PIN);

selector_t selector = HMIN;
selector_t lastState = HMIN;

int hMin = DEFAULT_HMIN;
int lastMin = hMin;

int hMax = DEFAULT_HMAX;
int lastMax = hMax;

int celsius = thermistor.getCelsius();
int lastCelsius = celsius;

void setup(){
    lcd.begin();

    lcd.setCursor(0, 0);
    lcd.print(">");
    lcd.setCursor(1, 0);
    lcd.print("HMIN:");
    lcd.print(hMin);
    lcd.setCursor(1, 1);
    lcd.print("HMAX:");
    lcd.print(hMax);
    lcd.setCursor(10, 0);
    lcd.print("CURR:");
    lcd.setCursor(10, 1);
    lcd.print(celsius);
}

void loop(){
    celsius = thermistor.getCelsius();

    if(celsius != lastCelsius){
        lcd.setCursor(10, 1);
        lcd.print("     ");
        lcd.setCursor(10, 1);
        lcd.print(celsius);
        lastCelsius = celsius;
    }

    if(celsius > hMin && celsius < hMax){
        relay.setState(lastState == HMIN);
    }else if(celsius <= hMin){
        relay.setState(true);
        lastState = HMIN;
    }else if(celsius >= hMax){
        relay.setState(false);
        lastState = HMAX;
    }

    switchButton.scanButtonState();
    if(switchButton.getButtonPressed()){
        selector = selector == HMIN ? HMAX : HMIN;
        lcd.setCursor(0, selector == HMAX ? 0 : 1);
        lcd.print(" ");
        lcd.setCursor(0, selector == HMIN ? 0 : 1);
        lcd.print(">");
        delay(DELAY);
        return;
    }

    plusButton.scanButtonState();
    minusButton.scanButtonState();

    if(selector == HMIN){
        if(plusButton.getButtonPressed()){
            x10Button.scanButtonState();
            hMin += x10Button.getButtonDown() ? 10 : 1;
        }
        if(minusButton.getButtonPressed()){
            x10Button.scanButtonState();
            hMin -= x10Button.getButtonDown() ? 10 : 1;
        }

        hMin = constrain(hMin, MIN_HMIN, hMax);

        if(hMin != lastMin){
            lcd.setCursor(6, 0);
            lcd.print("    ");
            lcd.setCursor(6, 0);
            lcd.print(hMin);
            lastMin = hMin;
        }

        delay(DELAY);
        return;
    }else{
        if(plusButton.getButtonPressed()){
            x10Button.scanButtonState();
            hMax += x10Button.getButtonDown() ? 10 : 1;
        }
        if(minusButton.getButtonPressed()){
            x10Button.scanButtonState();
            hMax -= x10Button.getButtonDown() ? 10 : 1;
        }

        hMax = constrain(hMax, hMin, MAX_HMAX);

        if(hMax != lastMax){
            lcd.setCursor(6, 1);
            lcd.print("    ");
            lcd.setCursor(6, 1);
            lcd.print(hMax);
            lastMax = hMax;
        }

        delay(DELAY);
        return;
    }
}
