#include "PIDController.h"

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
