#include <Encoder.h>

// src/config.h
#define SERIAL_BAUD 9600

#define ENCODER_A 2
#define ENCODER_B 3

#define MOTOR_ENA 9
#define MOTOR_IN1 6
#define MOTOR_IN2 5
#define SPEED_STEP 10

#define MAX_SPEED_PER_SECOND 5400
#define PERIOD_UPDATE_MS 1000

// lib/L298N/L298N.h
class L298N{
    public:
        int in1;
        int in2;
        int en;
        int speed = 0;
        int targetSpeed = 0;

        L298N(int in1, int in2, int en);
        void setSpeed(int speed);
};

// lib/L298N/L298N.cpp
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

    while(this->speed != this->targetSpeed){
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

        delay(100);
    }
}

// lib/PIDController/PIDController.h
class PIDController {
    public:
        Encoder *encoder;
        L298N *motor;

        int vDesired = 0;
        int encoderValue = 0;

        float kp = 0.015;
        float ki = 0.02;
        float kd = 0.07;
    public:
        PIDController(Encoder *encoder, L298N *motor);
        void update();
        void setDesiredSpeed(int speed);
        int getEncoderValue();
};

// lib/PIDController/PIDController.cpp
PIDController::PIDController(Encoder *encoder, L298N *motor): encoder(encoder), motor(motor){}

void PIDController::update(){
    int err = vDesired - encoderValue;
    int targetSpeed = kp * err;

    motor->setSpeed(constrain(targetSpeed, 1, 255));

    encoder->write(0);
    delay(PERIOD_UPDATE_MS);
    encoderValue = encoder->read();
}

void PIDController::setDesiredSpeed(int speed){
    this->vDesired = speed;
}

int PIDController::getEncoderValue(){
    return encoderValue;
}

// src/main.cpp
L298N motor(MOTOR_ENA, MOTOR_IN1, MOTOR_IN2);
Encoder encoder(ENCODER_A, ENCODER_B);
PIDController pid(&encoder, &motor);

void setup(){
    Serial.begin(SERIAL_BAUD);
    pid.setDesiredSpeed(2700);
}

void loop(){
    pid.update();
    Serial.println(pid.encoderValue);
}
