#ifndef PID_CONROLLER_H
#define PID_CONROLLER_H

#define TOLERANCE 10
#define CALIBRATION_PERIOD_MS 1000
#define MEASURE_HISTORY_SIZE 10
#define VARIATION_MIN_TOLERANCE 10
#define VARIATION_MAX_TOLERANCE 20
#define MAX_SPEED_PER_SECOND 5364 

#include <Arduino.h>
#include <Encoder.h>
#include "L298N.h"

/* 
    * Comparison enum:
    * EQUAL
    * GREATER
    * LESS
*/
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
        /*
            * Constructor
            * @param encoder: encoder object
            * @param motor: motor object
        */
        PIDController(Encoder encoder, L298N motor);

        /*
            * Call PID controller update and set motor speed
            * Call this function in loop
            * @return: void
        */
        void update();

        /*
            * Set desired speed
            * @param speed: desired speed
            * @return: void
        */
        void setDesiredSpeed(int speed);

        float getKp();
};

/*
    * Compare two integers with tolerance
    * @param a: first integer
    * @param b: second integer
    * @param tolerance: tolerance
    * @return: 
    *   EQUAL if a and b are within tolerance, 
    *   GREATER if a is greater than b, 
    *   LESS if a is less than b
*/
comparison closeCompare(int a, int b, int tolerance);

#endif