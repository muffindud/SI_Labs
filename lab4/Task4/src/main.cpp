#include <Arduino.h>

#include "config.h"

#include "Relay.h"
#include "L298N.h"

#if !TINKERCAD
    #include "SerialMap.h"
#else
    #include "LCD.h"
    LCD lcd = LCD(LCD_ADDR, LCD_COLS, LCD_ROWS);
#endif

Relay relay(RELAY_IN);
L298N motor(MOTOR_IN1, MOTOR_IN2, MOTOR_EN);

String inputBuffer = "";

int getPercentage(String input){
    bool negative = false;

    if(input[input.length() - 1] != '%'){
        return -1;
    }

    if(input[0] == '-'){
        negative = true;
        input.remove(0, 1);
    }

    for(unsigned int i = 0; i < input.length() - 1; i++){
        if(input[i] < '0' || input[i] > '9'){
            return -1;
        }
    }

    int percentage = input.substring(0, input.length() - 1).toInt();

    return negative ? -percentage : percentage;
}

void setup(){
    #if !TINKERCAD
        stdinToSerial();
        redirectStdout();

        stdoutToLCD();
        clearLCD();
        printf("%d%%", motor.getSpeed());
    #else
        Serial.begin(SERIAL_BAUD);

        lcd.begin();
        lcd.print(motor.getSpeed());
        lcd.print("%");
    #endif
}

void loop(){
    if(motor.getSpeed() != motor.getTargetSpeed()){
        motor.setSpeed();

        #if !TINKERCAD
            stdoutToLCD();
            clearLCD();
            printf("%d%%", motor.getSpeed());
        #else
            lcd.clear();
            lcd.print(motor.getSpeed());
            lcd.print("%");
        #endif
    }

    #if !TINKERCAD
        char c = getchar();

        if(c){
            stdoutToSerial();

            if(c == 13){
                if(inputBuffer == "ON"){
                    relay.setState(true);
                }else if(inputBuffer == "OFF"){
                    relay.setState(false);
                }else{
                    if(getPercentage(inputBuffer) != -1){
                        motor.setTargetSpeed(getPercentage(inputBuffer));
                    }else if(inputBuffer.length() > 0){
                        printf("\nInvalid input: %s", inputBuffer.c_str());
                    }
                }

                inputBuffer = "";
            }else if(c == 127){
                if(inputBuffer.length() > 0)
                    inputBuffer.remove(inputBuffer.length() - 1);
            }else if(c == 8){
                if(inputBuffer.length() > 0)
                    inputBuffer.remove(inputBuffer.length() - 1);
                c = 127;
            }else if(c != 127 && c != 13 && c != 10 && c != 8){
                inputBuffer += c;
            }

            printf("%c", c);
        }
    #else
        inputBuffer = Serial.readStringUntil('\n');

        if(inputBuffer[inputBuffer.length() - 1] == 13){
            inputBuffer.remove(inputBuffer.length() - 1);
        }

        if (inputBuffer != ""){
            Serial.println(inputBuffer);

            if(inputBuffer == "ON"){
                relay.setState(true);
            }else if(inputBuffer == "OFF"){
                relay.setState(false);
            }else{
                int percentage = getPercentage(inputBuffer);
                if(percentage != -1){
                    motor.setTargetSpeed(percentage);
                }else if(inputBuffer.length() > 0){
                    Serial.print("\nInvalid input: ");
                    Serial.println(inputBuffer);
                }
            }

            inputBuffer = "";
        }
    #endif
}
