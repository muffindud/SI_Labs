#include <Encoder.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

#define ENCODER_A 6
#define ENCODER_B 7

#define MOTOR_ENA 3
#define MOTOR_IN1 4
#define MOTOR_IN2 5
#define SPEED_STEP 1

class L298N{
    private:
        int in1;
        int in2;
        int en;
        int speed = 0;
        int targetSpeed = 0;
        int analogMap(int speed);
    public:
        L298N(int in1, int in2, int en);
        void setTargetSpeed(int speed);
        void setSpeed();
        void applySpeed();
        int getSpeed();
        int getTargetSpeed();
};

L298N::L298N(int in1, int in2, int en){
    this->in1 = in1;
    this->in2 = in2;
    this->en = en;
    this->speed = 0;

    pinMode(this->in1, OUTPUT);
    pinMode(this->in2, OUTPUT);
    pinMode(this->en, OUTPUT);
}

void L298N::setTargetSpeed(int speed){
    if(speed > 100){
        this->targetSpeed = 100;
    }else if(speed < -100){
        this->targetSpeed = -100;
    }else{
        this->targetSpeed = speed;
    }
}

void L298N::setSpeed(){
    if(this->targetSpeed > this->speed){
        this->speed += SPEED_STEP;
    }else if(this->targetSpeed < this->speed){
        this->speed -= SPEED_STEP;
    }

    this->applySpeed();

    delay(10);
}

void L298N::applySpeed(){
    if(this->speed == 0){
        analogWrite(this->en, 0);
        digitalWrite(this->in1, LOW);
        digitalWrite(this->in2, LOW);
    }else if(this->speed > 0){
        analogWrite(this->en, this->analogMap(this->speed));
        digitalWrite(this->in1, HIGH);
        digitalWrite(this->in2, LOW);
    }else if(this->speed < 0){
        analogWrite(this->en, this->analogMap(this->speed));
        digitalWrite(this->in1, LOW);
        digitalWrite(this->in2, HIGH);
    }
}

int L298N::getSpeed(){
    return this->speed;
}

int L298N::analogMap(int speed){
    speed = abs(speed);

    return (int)map(speed, 0, 100, 0, 255);
}

int L298N::getTargetSpeed(){
    return this->targetSpeed;
}

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);
L298N motor(MOTOR_ENA, MOTOR_IN1, MOTOR_IN2);
Encoder encoder(ENCODER_A, ENCODER_B);

void setup(){
    lcd.begin(LCD_COLS, LCD_ROWS);
}

void loop(){

}
