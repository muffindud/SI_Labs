#ifndef USART_HANDLER_H
#define USART_HANDLER_H

#define STX_MARK 0x02
#define ETX_MARK 0x03

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
    unsigned short int STX = STX_MARK;
    unsigned int P_NR;
    unsigned int SRC;
    unsigned int DST;
    PacketType_T P_ID;
    Command_T CMD;
    unsigned long int DATA;
    unsigned short int ETX = ETX_MARK;
};

const int packetSize = sizeof(ProtocolFrame);

/*
    * @brief: Encode a ProtocolFrame struct into a byte array
    * @param: ProtocolFrame frame - the frame to be encoded
    * @param: byte* buffer - the buffer to store the encoded frame
*/
void encodeFrame(ProtocolFrame frame, byte* buffer);

/*
    * @brief: Decode a byte array into a ProtocolFrame struct
    * @param: byte* buffer - the buffer to be decoded
    * @param: ProtocolFrame* frame - the frame to store the decoded data
*/
void decodeFrame(byte* buffer, ProtocolFrame* frame);

#endif
