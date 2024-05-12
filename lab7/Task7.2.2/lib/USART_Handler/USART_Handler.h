#ifndef USART_HANDLER_H
#define USART_HANDLER_H

#include <Arduino.h>

enum PacketType_T{
    TEMP,
    HUMIDITY,
    PRESSURE,
    LIGHT,
    ERROR
};

enum Command_T{
    DATA,
    ACK,
    NACK
};

struct ProtocolFrame{
    unsigned short int STX = 0x02;
    unsigned int P_NR;
    unsigned int SRC;
    unsigned int DST;
    PacketType_T P_ID;
    Command_T CMD;
    unsigned long int DATA;
    unsigned short int ETX = 0x03;
};

const int packetSize = sizeof(ProtocolFrame);

#endif
