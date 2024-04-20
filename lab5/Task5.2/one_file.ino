#include <Encoder.h>

// src/config.h
#define SERIAL_BAUD 9600

#define ENCODER_A 2
#define ENCODER_B 3

#define MOTOR_ENA 9
#define MOTOR_IN1 6
#define MOTOR_IN2 5
#define SPEED_STEP 10

#define MAX_SPEED_PER_SECOND 5364

// lib/L298N/L298N.h
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
        void setSpeed(int speed);
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

void L298N::setSpeed(int speed){
    if(speed > 100){
        this->targetSpeed = 100;
    }else if(speed < -100){
        this->targetSpeed = -100;
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
            analogWrite(this->en, this->analogMap(this->speed));
            digitalWrite(this->in1, HIGH);
            digitalWrite(this->in2, LOW);
        }else if(this->speed < 0){
            analogWrite(this->en, this->analogMap(this->speed));
            digitalWrite(this->in1, LOW);
            digitalWrite(this->in2, HIGH);
        }
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

        int vDesired = 0;

        int vHistory[MEASURE_HISTORY_SIZE];
        bool historyFilled = false;
        void pushToHistory(int v);
        void emptyHistory();
        int getHistoryVariation();

        float kp = 0;
        bool kpCalibrated = false;
        void calibrateKp();

        float ki = 0;
        bool kiCalibrated = false;
        void calibrateKi();

        float kd = 0;
        bool kdCalibrated = false;
        void calibrateKd();
    public:
        int encoderValue;
        PIDController(Encoder encoder, L298N motor);
        void update();
        void setDesiredSpeed(int speed);
        float getKp();
};

comparison closeCompare(int a, int b, int tolerance);

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
        
    }else if(variation > VARIATION_MAX_TOLERANCE){
        
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
    int v = encoder.read();
    encoderValue = v;

    pushToHistory(v);

    // if(!kpCalibrated && historyFilled){
    //     calibrateKp();
    // }

    encoder.write(0);
    delay(CALIBRATION_PERIOD_MS);
}

void PIDController::setDesiredSpeed(int speed){
    vDesired = speed;

    kpCalibrated = false;
    kiCalibrated = false;
    kdCalibrated = false;
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

// src/main.cpp
L298N motor(MOTOR_ENA, MOTOR_IN1, MOTOR_IN2);
Encoder encoder(ENCODER_A, ENCODER_B);

PIDController pid(encoder, motor);

void setup(){
    Serial.begin(SERIAL_BAUD);
    motor.setSpeed(50);
}

void loop(){
}
