#include "L298N.h"

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

    delay(10);
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
