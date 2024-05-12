#include "USART_Handler.h"

void encodeFrame(ProtocolFrame frame, byte* buffer){
    buffer[0] = frame.STX;
    buffer[1] = (frame.P_NR >> 8) & 0xFF;
    buffer[2] = frame.P_NR & 0xFF;
    buffer[3] = (frame.SRC >> 8) & 0xFF;
    buffer[4] = frame.SRC & 0xFF;
    buffer[5] = (frame.DST >> 8) & 0xFF;
    buffer[6] = frame.DST & 0xFF;
    for(int j = 0; j < sizeof(PacketType_T); j++){
        buffer[7 + j] = ((byte*)&frame.P_ID)[j];
    }
    for(int j = 0; j < sizeof(Command_T); j++){
        buffer[7 + sizeof(PacketType_T) + j] = ((byte*)&frame.CMD)[j];
    }
    buffer[8 + sizeof(PacketType_T) + sizeof(Command_T)] = frame.CMD;
    buffer[9 + sizeof(PacketType_T) + sizeof(Command_T)] = (frame.DATA >> 24) & 0xFF;
    buffer[10 + sizeof(PacketType_T) + sizeof(Command_T)] = (frame.DATA >> 16) & 0xFF;
    buffer[11 + sizeof(PacketType_T) + sizeof(Command_T)] = (frame.DATA >> 8) & 0xFF;
    buffer[12 + sizeof(PacketType_T) + sizeof(Command_T)] = frame.DATA & 0xFF;
    buffer[13 + sizeof(PacketType_T) + sizeof(Command_T)] = frame.ETX;
}

void decodeFrame(byte* buffer, ProtocolFrame* frame){
    frame->STX = buffer[0];
    frame->P_NR = (buffer[1] << 8) | buffer[2];
    frame->SRC = (buffer[3] << 8) | buffer[4];
    frame->DST = (buffer[5] << 8) | buffer[6];
    for(int j = 0; j < sizeof(PacketType_T); j++){
        ((byte*)&frame->P_ID)[j] = buffer[7 + j];
    }
    for(int j = 0; j < sizeof(Command_T); j++){
        ((byte*)&frame->CMD)[j] = buffer[7 + sizeof(PacketType_T) + j];
    }
    frame->DATA = 
        buffer[9 + sizeof(PacketType_T) + sizeof(Command_T)] << 24 | 
        buffer[10 + sizeof(PacketType_T) + sizeof(Command_T)] << 16 | 
        buffer[11 + sizeof(PacketType_T) + sizeof(Command_T)] << 8 | 
        buffer[12 + sizeof(PacketType_T) + sizeof(Command_T)];
    frame->ETX = buffer[13 + sizeof(PacketType_T) + sizeof(Command_T)];
}
