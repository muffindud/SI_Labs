#define ENC_A_PIN 2
#define ENC_B_PIN 3

#define MOTOR_ENA_PIN 9
#define MOTOR_IN1_PIN 5
#define MOTOR_IN2_PIN 6

#define TIME_UNIT_MS 1000
#define PWM_MIN 1
#define PWM_MAX 255
#define MAX_TPS 5400
#define MAX_TP_TIME_UNIT (MAX_TPS * TIME_UNIT_MS / 1000)

#define SERIAL_BAUD 9600

#define KP 0.05
#define KI 0.0
#define KD 0.0

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
        analogWrite(MOTOR_ENA_PIN, constrain(abs(motorPWM), PWM_MIN, PWM_MAX));

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

        // delay(10);
    }
}

void applyPID(int targetTPS){
    static int lastError = 0;
    static int integral = 0;
    targetTPS = targetTPS * TIME_UNIT_MS / 1000;

    encoder.write(0);
    delay(TIME_UNIT_MS);
    int ticks = encoder.read();

    int error = targetTPS - ticks;

    integral += error;
    int derivative = error - lastError;

    int pwm = KP * error + KI * integral + KD * derivative;
    setPWM(pwm);

    lastError = error;
}

void setup(){
    Serial.begin(SERIAL_BAUD);
    pinMode(MOTOR_ENA_PIN, OUTPUT);
    pinMode(MOTOR_IN1_PIN, OUTPUT);
    pinMode(MOTOR_IN2_PIN, OUTPUT);
}

void loop(){
    applyPID(2700);
    Serial.println(encoder.read());
}
