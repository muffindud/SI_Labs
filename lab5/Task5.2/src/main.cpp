#include <Arduino.h>
#include <Encoder.h>
#include <LiquidCrystal_I2C.h>

#include "L298N.h"

#include "config.h"

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);
L298N motor(MOTOR_ENA, MOTOR_IN1, MOTOR_IN2);
Encoder encoder(ENCODER_A, ENCODER_B);

void setup(){
    lcd.begin(LCD_COLS, LCD_ROWS);
}

void loop(){

}
