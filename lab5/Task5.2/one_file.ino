#define ENC_A_PIN 2
#define ENC_B_PIN 3

#define MOTOR_ENA_PIN 9
#define MOTOR_IN1_PIN 5
#define MOTOR_IN2_PIN 6

#define PWM_MAX 255
#define MAX_TICKS_PER_SECOND 5400

#define SERIAL_BAUD 9600

#include <Encoder.h>

Encoder encoder(ENC_A_PIN, ENC_B_PIN);

int motorPWM = 0;

void setPWM(int pwm){
    pwm = constrain(pwm, -PWM_MAX, PWM_MAX);

    while(motorPWM != pwm){
        if(motorPWM < pwm){
            motorPWM++;
        }else{
            motorPWM--;
        }
        analogWrite(MOTOR_ENA_PIN, motorPWM);

        if(motorPWM > 0){
            digitalWrite(MOTOR_IN1_PIN, HIGH);
            digitalWrite(MOTOR_IN2_PIN, LOW);
        }else if(motorPWM < 0){
            digitalWrite(MOTOR_IN1_PIN, LOW);
            digitalWrite(MOTOR_IN2_PIN, HIGH);
        }else if(motorPWM == 0){
            digitalWrite(MOTOR_IN1_PIN, LOW);
            digitalWrite(MOTOR_IN2_PIN, LOW);
        }

        delay(10);
    }
}

void setup(){
    Serial.begin(SERIAL_BAUD);
    pinMode(MOTOR_ENA_PIN, OUTPUT);
    pinMode(MOTOR_IN1_PIN, OUTPUT);
    pinMode(MOTOR_IN2_PIN, OUTPUT);
}

void loop(){

}
