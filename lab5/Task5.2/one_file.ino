#include <Encoder.h>

// src/config.h
#define SERIAL_BAUD 9600

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

#define ENCODER_A 6
#define ENCODER_B 7

#define MOTOR_ENA 3
#define MOTOR_IN1 4
#define MOTOR_IN2 5
#define SPEED_STEP 1

#define TINKERCAD 1

// lib/L298N/L298N.h
class L298N{
    private:
        int in1;
        int in2;
        int en;
        int speed = 0;
        int targetSpeed = 0;
        int analogMap(int speed);
        void applySpeed();
    public:
        L298N(int in1, int in2, int en);
        void setTargetSpeed(int speed);
        void setSpeed();
        int getSpeed();
        int getTargetSpeed();
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

// lib/SerialMap/SerialMap.cpp
#if !TINKERCAD
#include <stdio.h>

FILE *_stdin;
FILE *_stdout;

bool serialEnabled = false;

static int getCharSerial(__attribute__((unused)) FILE *stream){
    if(Serial.available())
        return Serial.read();

    return -1;
}

static int putChar(char c, __attribute__((unused)) FILE *stream){
    int ret;

    if(c == 127){
        Serial.write(8);
        ret = Serial.write(' ');
        Serial.write(8);
    }else if(c == 10 || c == 13){
        ret = Serial.write(13) && Serial.write(10);
    }
    else{ 
        ret = Serial.write(c);
    }

    return ret == 1 ? 0 : -1;
}

void redirectSTDOUT(){
    if(!serialEnabled){
        Serial.begin(SERIAL_BAUD);
        serialEnabled = true;
    }

    _stdout = fdevopen(&putChar, NULL);
}

void redirectSTDIN(){
    if(!serialEnabled)
        Serial.begin(SERIAL_BAUD);
    
    serialEnabled = true;

    _stdin = fdevopen(NULL, &getCharSerial);
}
#endif

// src/main.cpp
L298N motor(MOTOR_ENA, MOTOR_IN1, MOTOR_IN2);
Encoder encoder(ENCODER_A, ENCODER_B);

void setup(){
    #if TINKERCAD
        Serial.begin(SERIAL_BAUD);
    #else
        redirectSTDOUT();
        redirectSTDIN();
    #endif
}

void loop(){
    motor.setSpeed();

    #if TINKERCAD
        Serial.print("Speed: ");
        Serial.println(motor.getSpeed());
    #else
        printf("Speed: %d\n", motor.getSpeed());
    #endif
}
