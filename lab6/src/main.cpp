#include <Arduino.h>
#include "config.h"
#include "Led.h"
#include "Button.h"

Led green1(GREEN_1_PIN);
Led yellow1(YELLOW_1_PIN);
Led red1(RED_1_PIN);

Led green2(GREEN_2_PIN);
Led yellow2(YELLOW_2_PIN);
Led red2(RED_2_PIN);

Led inputIndex0(BIN_0_PIN);
Led inputIndex1(BIN_1_PIN);
Led inputIndex2(BIN_2_PIN);
Led inputIndex3(BIN_3_PIN);
Led inputIndex4(BIN_4_PIN);
Led inputIndex5(BIN_5_PIN);

Led bin0(BIN_6_PIN);
Led bin1(BIN_7_PIN);

Button button0(BUTTON_0_PIN);
Button button1(BUTTON_1_PIN);

struct FSM{
    unsigned long out;
    unsigned long timeS;
    unsigned long next[4];
};

FSM fsm[] = {
    {0b100001, 1, {0, 1, 0, 1}},
    {0b010011, 2, {2, 2, 2, 2}},
    {0b001100, 1, {2, 2, 3, 3}},
    {0b011010, 2, {0, 0, 0, 0}}
};

int state = 0;

int getInput(){
    button0.scanButtonState();
    button1.scanButtonState();

    return (byte)button0.getButtonDown() * 0b10 + (byte)button1.getButtonDown() * 0b01;
}

int setOutput(int state){
    green1.setPowerState(state & 0b100000);
    yellow1.setPowerState(state & 0b010000);
    red1.setPowerState(state & 0b001000);

    green2.setPowerState(state & 0b000100);
    yellow2.setPowerState(state & 0b000010);
    red2.setPowerState(state & 0b000001);

    return 0;
}

void setup(){
    
}

void loop(){
    int out = fsm[state].out;
    inputIndex0.setPowerState(out & 0b100000);
    inputIndex1.setPowerState(out & 0b010000);
    inputIndex2.setPowerState(out & 0b001000);
    inputIndex3.setPowerState(out & 0b000100);
    inputIndex4.setPowerState(out & 0b000010);
    inputIndex5.setPowerState(out & 0b000001);
    setOutput(out);
    delay(fsm[state].timeS * 1000);
    int input = getInput();
    state = fsm[state].next[input];
    bin0.setPowerState(state & 0b10);
    bin1.setPowerState(state & 0b01);
}
