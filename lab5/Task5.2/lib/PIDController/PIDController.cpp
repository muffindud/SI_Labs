#include "PIDController.h"

PIDController::PIDController(Encoder encoder, L298N motor): 
    encoder(encoder),
    motor(motor){}

void PIDController::update(){
    motor.setSpeed();
    int v = encoder.read();
    comparison pStateComp = closeCompare(v, vDesired / 2, TOLERANCE);
    
    if(pStateComp == GREATER){
        

        return;
    }else if(pStateComp == LESS){
        
        return;
    }

    // TODO: Implement I state

    // TODO: Implement D state
}

void PIDController::setDesiredSpeed(int speed){
    this->vDesired = speed;
}

comparison closeCompare(int a, int b, int tolerance){
    if(abs(a - b) <= tolerance){
        return EQUAL;
    }else if(a > b){
        return GREATER;
    }else if(a < b){
        return LESS;
    }
}
