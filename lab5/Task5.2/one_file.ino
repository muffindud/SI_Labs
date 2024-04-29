#define ENC_A_PIN 2
#define ENC_B_PIN 3

#define MOTOR_ENA_PIN 9
#define MOTOR_IN1_PIN 5
#define MOTOR_IN2_PIN 6

#define PWM_MIN 1
#define PWM_MAX 255

#define MAX_TPS 5400
#define TIME_UNIT_MS 1000

#define SERIAL_BAUD 9600

#define KP 0.01
#define KI 0.01
#define KD 0.005

#define MOTOR_TPRPM 15

#include <Encoder.h>

Encoder encoder(ENC_A_PIN, ENC_B_PIN);

int motorPWM = 0;

void setPWM(int pwm){
    pwm = constrain(pwm, PWM_MIN, PWM_MAX);

    while(motorPWM != pwm){
        if(motorPWM < pwm){
            motorPWM++;
        }else{
            motorPWM--;
        }
        analogWrite(MOTOR_ENA_PIN, constrain(motorPWM, PWM_MIN, PWM_MAX));

        digitalWrite(MOTOR_IN1_PIN, HIGH);
        digitalWrite(MOTOR_IN2_PIN, LOW);

        // delay(10);
    }
}

int lastError = 0;
int integral = 0;
void applyPID(int targetRPM, bool printReslts = false){
  	int targetTPS = targetRPM * MOTOR_TPRPM;

    int ticks = encoder.read();
    int error = targetTPS - ticks;

    integral += error;
    int derivative = error - lastError;

    int pwm = KP * error + KI * integral + KD * derivative;

    if(printReslts){
        Serial.println("==================================");
        
        Serial.print("Ticks: ");
        Serial.println(ticks);

        Serial.print("RPM: ");
        Serial.println((int)(ticks / MOTOR_TPRPM));
        
        Serial.print(" P: ");
        Serial.print(error);
        Serial.print(" * ");
        Serial.print(KP);
        Serial.print(" = ");
        Serial.println(error * KP);
        
        Serial.print(" I: ");
        Serial.print(integral);
        Serial.print(" * ");
        Serial.print(KI);
        Serial.print(" = ");
        Serial.println(integral * KI);
        
        Serial.print(" D: ");
        Serial.print(derivative);
        Serial.print(" * ");
        Serial.print(KD, 3);
        Serial.print(" = ");
        Serial.println(derivative * KD);
        
        Serial.print(" PWM: ");
        Serial.println(pwm);
    }

    setPWM(pwm);

    lastError = error;

    encoder.write(0);
    delay(TIME_UNIT_MS);
}

void setup(){
    Serial.begin(SERIAL_BAUD);
    pinMode(MOTOR_ENA_PIN, OUTPUT);
    pinMode(MOTOR_IN1_PIN, OUTPUT);
    pinMode(MOTOR_IN2_PIN, OUTPUT);
    encoder.write(0);
}

int targetRPM = 255;

void loop(){
    applyPID(targetRPM, true);
    
    // String input = Serial.readStringUntil('\n');
    // if(input[input.length() - 1] == 13){
    //     input.remove(input.length() - 1);
    // }

    // if(input != ""){
    //     targetRPM = input.toInt();
    //     integral = 0;
    //     lastError = 0;
    // }
}
