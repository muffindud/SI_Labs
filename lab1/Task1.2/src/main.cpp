#define GREEN_LED_PIN 12
#define RED_LED_PIN 13

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#include <Arduino.h>

#include "Keypad.h"
#include "Led.h"
#include "LCD.h"

char keyMap[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins[KEYPAD_ROWS] = {7, 6, 5, 4};
byte colPins[KEYPAD_COLS] = {3, 2, 1, 0};

Keypad keyPad = Keypad(
    makeKeymap(keyMap),
    rowPins,
    colPins,
    KEYPAD_ROWS,
    KEYPAD_COLS
);
Led greenLed = Led(GREEN_LED_PIN);
Led redLed = Led(RED_LED_PIN);

LCD lcd = LCD(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

// Max length of password is 16
String password = "";
String input = "";

// Set new password
void newPassword(){
    lcd.clear();
    lcd.print("New password:");
    lcd.setCursor(0, 1);

    greenLed.setPowerState(false);
    redLed.setPowerState(false);

    input = "";

    while(true){
        char key = keyPad.getKey();

        if(key){
            if(key == '#'){
                if(input.length() > 0){
                    password = input;
                    break;
                }
            }
            else if(input.length() < LCD_COLUMNS){
                input += key;
                lcd.print("*");
            }
        }
    }

    return;
}

// Reset the screen
void screenRst(){
    if(password == ""){
        newPassword();
    }

    lcd.clear();
    lcd.print("Enter password:");
    lcd.setCursor(0, 1);

    greenLed.setPowerState(false);
    redLed.setPowerState(false);

    input = "";

    return;
}

void askNewPassword(){
    lcd.clear();
    lcd.print("New pass? (0/1)");

    while(true){
        char key = keyPad.getKey();

        if(key){
            if(key == '0'){
                return;
            }
            else if(key == '1'){
                password = "";
                newPassword();
                return;
            }
        }
    }
}

void setup(){
    greenLed.setup();
    redLed.setup();
    lcd.begin();

    screenRst();
}

void loop(){
    char key = keyPad.getKey();
    
    if(key){
        if(key == '#'){
            lcd.clear();

            if(input == password){
                greenLed.setPowerState(true);
                lcd.print("Access granted");
                delay(2000);
                askNewPassword();
            }
            else{
                redLed.setPowerState(true);
                lcd.print("Access denied");
                delay(2000);
            }
            
            screenRst();
        }
        else if(input.length() < LCD_COLUMNS){
            input += key;
            lcd.print("*");
        }
    }
}
