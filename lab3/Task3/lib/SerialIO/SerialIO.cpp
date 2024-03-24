#define SERIAL_BAUD_RATE 4000000

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

SerialIO::SerialIO(){} 

void SerialIO::setup(){
    Serial.begin(SERIAL_BAUD_RATE);

    FILE *_stdin, *_stdout, *_stderr;

    _stdin = stdioOpenStream(&Serial, true, false);
    _stdout = stdioOpenStream(&Serial, false, true);
    _stderr = stdioOpenStream(&Serial, false, true);
    __iob[2] = _stderr;

    delay(100);
}
