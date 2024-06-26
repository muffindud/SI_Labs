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

void L298N::setSpeed(int speed){
    if(speed > 255){
        this->targetSpeed = 255;
    }else if(speed < -255){
        this->targetSpeed = -255;
    }else{
        this->targetSpeed = speed;
    }

    while(true){
        if(this->targetSpeed > this->speed){
            if(this->speed + SPEED_STEP > this->targetSpeed){
                this->speed = this->targetSpeed;
            }else{
                this->speed += SPEED_STEP;
            }
        }else if(this->targetSpeed < this->speed){
            if(this->speed - SPEED_STEP < this->targetSpeed){
                this->speed = this->targetSpeed;
            }else{
                this->speed -= SPEED_STEP;
            }
        }

        if(this->speed == 0){
            analogWrite(this->en, 0);
            digitalWrite(this->in1, LOW);
            digitalWrite(this->in2, LOW);
        }else if(this->speed > 0){
            analogWrite(this->en, abs(this->speed));
            digitalWrite(this->in1, HIGH);
            digitalWrite(this->in2, LOW);
        }else if(this->speed < 0){
            analogWrite(this->en, abs(this->speed));
            digitalWrite(this->in1, LOW);
            digitalWrite(this->in2, HIGH);
        }
    }
}

int L298N::getSpeed(){
    return this->speed;
}

int L298N::getTargetSpeed(){
    return this->targetSpeed;
}
