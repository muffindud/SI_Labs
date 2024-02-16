#define NEW_LINE_1 13
#define NEW_LINE_2 10
#define BACKSPACE 127
#define SERIAL_BAUD_RATE 9600

#include "SerialIO.h"

extern struct __file *__iob[];

static int stdioPutChar(char c, FILE *s) {
    Stream *stream = (Stream*)s->udata;

    return stream->write(c) == 1 ? 0 : -1;
}

static int stdioGetChar(FILE *s) {
    Stream *stream = (Stream*)s->udata;

    return stream->read();
}

FILE *stdioOpenStream(Stream *stream, boolean r, boolean w) {
    FILE *f;
    
    f = fdevopen(w ? stdioPutChar : NULL, r ? stdioGetChar : NULL);
    f->udata = stream;

    return f;
}

SerialIO::SerialIO(){
} 

void SerialIO::setup(){
    Serial.begin(SERIAL_BAUD_RATE);

    FILE *_stdin, *_stdout, *_stderr;

    _stdin = stdioOpenStream(&Serial, true, false);
    _stdout = stdioOpenStream(&Serial, false, true);
    _stderr = stdioOpenStream(&Serial, false, true);
    __iob[2] = _stderr;

    delay(100);
}

void SerialIO::waitInput(){
    if(Serial.available() > 0){
        input = getchar();

        if(input == NEW_LINE_1){
            printf("%s", new_line.c_str());
            handleCommand();
        }
        else if(input == BACKSPACE && command_buffer.length() > 0){
            command_buffer = command_buffer.substring(0, command_buffer.length() - 1);
            printf("%s", backspace.c_str());
        }
        else if(input != BACKSPACE && input != NEW_LINE_1 && input != NEW_LINE_2){
            command_buffer += input;
            putchar(input);
        }
    }
}

void SerialIO::serialDisplay(String message){
    printf("%s", message.c_str());
}

void SerialIO::handleBackspace(){
    if(command_buffer.length() > 0){
        command_buffer = command_buffer.substring(0, command_buffer.length() - 1);
        printf("%s", backspace.c_str());
    }
}

void SerialIO::printNewLine(){
    printf("%s", new_line.c_str());
    return;
}

void SerialIO::handleCommand(){
    // TODO: Implement command handling
    command_buffer = "";
    putchar(command_prompt);
}

void SerialIO::clearCommandBuffer(){
    command_buffer = "";
    return;
}

String SerialIO::getCommand(){
    return command_buffer;
}
