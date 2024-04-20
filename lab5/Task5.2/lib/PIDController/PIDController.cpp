#include "PIDController.h"

PIDController::PIDController(Encoder *encoder, L298N *motor): encoder(encoder), motor(motor){}

void PIDController::update(){
    int err = vDesired - encoderValue;
    motor->setSpeed(map(err * kp, 0, MAX_SPEED_PER_SECOND, 0, 255));

    encoder->write(0);
    delay(PERIOD_UPDATE_MS);
    encoderValue = encoder->read();
}

void PIDController::setDesiredSpeed(int speed){
    vDesired = speed;
}

int PIDController::getEncoderValue(){
    return encoderValue;
}
