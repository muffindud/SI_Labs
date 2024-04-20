#include <Encoder.h>

// src/config.h
#define SERIAL_BAUD 9600

#define ENCODER_A 2
#define ENCODER_B 3

#define MOTOR_ENA 7
#define MOTOR_IN1 6
#define MOTOR_IN2 5
#define SPEED_STEP 1

#define MAX_SPEED_PER_SECOND 5364

#define DC_416_RPM_FACTOR 15

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

// lib/PIDController/PIDController.h
#define TOLERANCE 10
#define CALIBRATION_PERIOD_MS 1000
#define MEASURE_HISTORY_SIZE 10
#define VARIATION_MIN_TOLERANCE 10
#define VARIATION_MAX_TOLERANCE 20

enum comparison{
    EQUAL,
    GREATER,
    LESS
};

class PIDController {
    private:
        Encoder encoder;
        L298N motor;

        int vHistory[MEASURE_HISTORY_SIZE];

        float kp = 0.5;
        float kpStep = 0.25;
        bool kpCalibrated = false;
        void calibrateKp();

        float ki = 0.5;
        float kiStep = 0.25;
        bool kiCalibrated = false;
        void calibrateKi();

        float kd = 0.5;
        float kdStep = 0.25;
        bool kdCalibrated = false;
        void calibrateKd();

        int vDesired = 0;

        bool historyFilled = false;
        void pushToHistory(int v);
        void emptyHistory();
        int getHistoryVariation();
    public:
        PIDController(Encoder encoder, L298N motor);
        void update();
        void setDesiredSpeed(int speed);
        float getKp();
};

// lib/PIDController/PIDController.cpp
PIDController::PIDController(Encoder encoder, L298N motor): encoder(encoder), motor(motor){
    emptyHistory();
}

void PIDController::pushToHistory(int v){
    for(int i = 0; i < MEASURE_HISTORY_SIZE - 1; i++){
        vHistory[i] = vHistory[i + 1];
    }

    vHistory[MEASURE_HISTORY_SIZE - 1] = v;

    historyFilled = vHistory[0] != -1;
}

void PIDController::emptyHistory(){
    for(int i = 0; i < MEASURE_HISTORY_SIZE; i++){
        vHistory[i] = -1;
    }

    historyFilled = false;
}

int PIDController::getHistoryVariation(){
    int variation = 0;

    for(int i = 0; i < MEASURE_HISTORY_SIZE - 1; i++){
        variation += abs(vHistory[i] - vHistory[i + 1]);
    }

    return variation;
}

void PIDController::calibrateKp(){
    int variation = getHistoryVariation();

    if(variation < VARIATION_MIN_TOLERANCE){
        kp += kpStep;
        kpStep /= 2;
        motor.setTargetSpeed(map(vDesired * kp, 0, MAX_SPEED_PER_SECOND, 0, 255));
    }else if(variation > VARIATION_MAX_TOLERANCE){
        kp -= kpStep;
        kpStep /= 2;
        motor.setTargetSpeed(map(vDesired * kp, 0, MAX_SPEED_PER_SECOND, 0, 255));
    }
    else{
        kpCalibrated = true;
    }
}

void PIDController::calibrateKi(){
    
}

void PIDController::calibrateKd(){
    
}

void PIDController::update(){
    motor.setSpeed();
    int v = encoder.read();

    pushToHistory(v);
    

    if(!historyFilled){
        return;
    }

    if(!kpCalibrated){
        calibrateKp();
    }

    delay(CALIBRATION_PERIOD_MS);
}

void PIDController::setDesiredSpeed(int speed){
    vDesired = speed;

    kpCalibrated = false;
    kpStep = 0.25;

    kiCalibrated = false;
    kiStep = 0.25;

    kdCalibrated = false;
    kdStep = 0.25;
}

float PIDController::getKp(){
    return kp;
}

comparison closeCompare(int a, int b, int tolerance){
    if(abs(a - b) <= tolerance){
        return EQUAL;
    }else if(a > b){
        return GREATER;
    }else if(a < b){
        return LESS;
    }

    return EQUAL;
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

PIDController pid(encoder, motor);

void setup(){
    Serial.begin(SERIAL_BAUD);
}

void loop(){
    pid.setDesiredSpeed(3600);
    pid.update();
}
