#include <Wire.h>

/*
    config.h
*/

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

#define SERIAL_BAUD 9600

#define RELAY_IN 4

#define MOTOR_IN1 2
#define MOTOR_IN2 3
#define MOTOR_EN 5
#define SPEED_STEP 1

#define TINKERCAD true

/*
    LCD.h
*/ 

struct OutputState
{
    uint8_t rs = 0;
    uint8_t rw = 0;
    uint8_t E = 0;
    uint8_t Led = 0;
    uint8_t data = 0;

    uint8_t GetLowData()
    {
        uint8_t buffer = rs;
        buffer |= rw << 1;
        buffer |= E << 2;
        buffer |= Led << 3;
        buffer |= (data & 0x0F) << 4;

        return buffer;
    }

    uint8_t GetHighData()
    {
        uint8_t buffer = rs;
        buffer |= rw << 1;
        buffer |= E << 2;
        buffer |= Led << 3;
        buffer |= (data & 0xF0);
        return buffer;
    }
};

class LCD : public Print
{
public:
    LCD(uint8_t address, uint8_t columns = 16, uint8_t rows = 2)
    : _address(address), _columnMax(--columns), _rowMax(--rows) {}

    void begin(bool beginWire = true);
    void backlight();
    void noBacklight();

    void clear();
    void home();
    void leftToRight();
    void rightToLeft();
    void autoscroll();
    void noAutoscroll();
    void display();
    void noDisplay();
    void cursor();
    void noCursor();
    void blink();
    void noBlink();
    void scrollDisplayLeft();
    void scrollDisplayRight();
    void createChar(uint8_t location, uint8_t charmap[]);
    void setCursor(uint8_t col, uint8_t row);

    // Method used by the Arduino class "Print" which is the one that provides the .print(string) method
    virtual size_t write(uint8_t character);

private:
    void InitializeLCD();
    void I2C_Write(uint8_t output);
    void LCD_Write(uint8_t output, bool initialization = false);

private:
    uint8_t _address;
    uint8_t _columnMax;
    uint8_t _rowMax;
    OutputState _output;
    uint8_t _displayState = 0x00;
    uint8_t _entryState = 0x00;
};

/*
    LCD.cpp
*/

void LCD::begin(bool beginWire)
{
    if (beginWire)
        Wire.begin();

    I2C_Write(0b00000000); // Clear i2c adapter
    delay(50); //Wait more than 40ms after powerOn.

    InitializeLCD();
}

void LCD::backlight()
{
    _output.Led = 1;
    I2C_Write(0b00000000 | _output.Led << 3); // Led pin is independent from LCD data and control lines.
}

void LCD::noBacklight()
{
    _output.Led = 0;
    I2C_Write(0b00000000 | _output.Led << 3); // Led pin is independent from LCD data and control lines.
}

void LCD::clear()
{
    _output.rs = 0;
    _output.rw = 0;

    LCD_Write(0b00000001);
    delayMicroseconds(1600);
}

void LCD::home()
{
    _output.rs = 0;
    _output.rw = 0;

    LCD_Write(0b00000010);
    delayMicroseconds(1600);
}

// Part of Entry mode set
void LCD::leftToRight()
{
    _output.rs = 0;
    _output.rw = 0;

    _entryState |= 1 << 1;

    LCD_Write(0b00000100 | _entryState);
    delayMicroseconds(37);
}

// Part of Entry mode set
void LCD::rightToLeft()
{
    _output.rs = 0;
    _output.rw = 0;

    _entryState &= ~(1 << 1);

    LCD_Write(0b00000100 | _entryState);
    delayMicroseconds(37);
}

// Part of Entry mode set
void LCD::autoscroll()
{
    _output.rs = 0;
    _output.rw = 0;

    _entryState |= 1;

    LCD_Write(0b00000100 | _entryState);
    delayMicroseconds(37);
}

// Part of Entry mode set
void LCD::noAutoscroll()
{
    _output.rs = 0;
    _output.rw = 0;

    _entryState &= ~1;

    LCD_Write(0b00000100 | _entryState);
    delayMicroseconds(37);
}

// Part of Display control
void LCD::display()
{
    _output.rs = 0;
    _output.rw = 0;

    _displayState |= 1 << 2;

    LCD_Write(0b00001000 | _displayState);
    delayMicroseconds(37);
}

// Part of Display control
void LCD::noDisplay()
{
    _output.rs = 0;
    _output.rw = 0;

    _displayState &= ~(1 << 2);

    LCD_Write(0b00001000 | _displayState);
    delayMicroseconds(37);
}

// Part of Display control
void LCD::cursor()
{
    _output.rs = 0;
    _output.rw = 0;

    _displayState |= 1 << 1;

    LCD_Write(0b00001000 | _displayState);
    delayMicroseconds(37);
}

// Part of Display control
void LCD::noCursor()
{
    _output.rs = 0;
    _output.rw = 0;

    _displayState &= ~(1 << 1);

    LCD_Write(0b00001000 | _displayState);
    delayMicroseconds(37);
}

// Part of Display control
void LCD::blink()
{
    _output.rs = 0;
    _output.rw = 0;

    _displayState |= 1;

    LCD_Write(0b00001000 | _displayState);
    delayMicroseconds(37);
}

// Part of Display control
void LCD::noBlink()
{
    _output.rs = 0;
    _output.rw = 0;

    _displayState &= ~1;

    LCD_Write(0b00001000 | _displayState);
    delayMicroseconds(37);
}

// Part of Cursor or display shift
void LCD::scrollDisplayLeft()
{
    _output.rs = 0;
    _output.rw = 0;

    LCD_Write(0b00011000);
    delayMicroseconds(37);
}

// Part of Cursor or display shift
void LCD::scrollDisplayRight()
{
    _output.rs = 0;
    _output.rw = 0;

    LCD_Write(0b00011100);
    delayMicroseconds(37);
}

// Set CGRAM address
void LCD::createChar(uint8_t location, uint8_t charmap[])
{
    _output.rs = 0;
    _output.rw = 0;

    location %= 8;

    LCD_Write(0b01000000 | (location << 3));
    delayMicroseconds(37);

    for (int i = 0; i < 8; i++)
        write(charmap[i]);

    setCursor(0, 0); // Set the address pointer back to the DDRAM
}

// Set DDRAM address
void LCD::setCursor(uint8_t col, uint8_t row)
{
    static const uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    _output.rs = 0;
    _output.rw = 0;

    if(col > _columnMax) { col = _columnMax; } // sanity limits
    if(row > _rowMax) { row = _rowMax; } // sanity limits

    uint8_t newAddress = row_offsets[row] + col;

    LCD_Write(0b10000000 | newAddress);
    delayMicroseconds(37);
}

size_t LCD::write(uint8_t character)
{
    _output.rs = 1;
    _output.rw = 0;

    LCD_Write(character);
    delayMicroseconds(41);

    return 1;
}

void LCD::InitializeLCD()
{
    // See HD44780U datasheet "Initializing by Instruction" Figure 24 (4-Bit Interface)
    _output.rs = 0;
    _output.rw = 0;

    LCD_Write(0b00110000, true);
    delayMicroseconds(4200);
    LCD_Write(0b00110000, true);
    delayMicroseconds(150);
    LCD_Write(0b00110000, true);
    delayMicroseconds(37);
    LCD_Write(0b00100000, true); // Function Set - 4 bits mode
    delayMicroseconds(37);
    LCD_Write(0b00101000); // Function Set - 4 bits(Still), 2 lines, 5x8 font
    delayMicroseconds(37);

    display();
    clear();
    leftToRight();
}

void LCD::I2C_Write(uint8_t output)
{
    Wire.beginTransmission(_address);
    Wire.write(output);
    Wire.endTransmission();
}

void LCD::LCD_Write(uint8_t output, bool initialization)
{
    _output.data = output;

    _output.E = true;
    I2C_Write(_output.GetHighData());
    delayMicroseconds(1); // High part of enable should be >450 nS

    _output.E = false;
    I2C_Write(_output.GetHighData());

    // During initialization we only send half a byte
    if (!initialization)
    {
        delayMicroseconds(37); // I think we need a delay between half byte writes, but no sure how long it needs to be.

        _output.E = true;
        I2C_Write(_output.GetLowData());
        delayMicroseconds(1); // High part of enable should be >450 nS

        _output.E = false;
        I2C_Write(_output.GetLowData());
    }
    //delayMicroseconds(37); // Some commands have different timing requirement,
                             // so every command should handle its own delay after execution
}

/*
    SerialMap.cpp
*/

#if !TINKERCAD
    #include <stdio.h>

    LCD *lcd = NULL;

    int lcdRow = 0;
    int lcdCol = 0;

    FILE *_stdin;
    FILE *_stdout;

    bool serialEnabled = false;
    bool serialPrint = false;

    static int getCharSerial(__attribute__((unused)) FILE *stream){
        if(Serial.available())
            return Serial.read();
    }

    static int putChar(char c, __attribute__((unused)) FILE *stream){
        int ret;

        if(serialPrint){
            if(c == 127){
                Serial.write(8);
                ret = Serial.write(' ');
                Serial.write(8);
            }else if(c == 10 || c == 13){
                ret = Serial.write(13) && Serial.write(10);
            }
            else{ 
                ret = Serial.write(c);
            }
        }else{
            if(c == 13){
                lcdCol = 0;
                lcdRow++;
                if(lcdRow >= LCD_ROWS){
                    lcdRow = 0;
                }
                ret = 1;
            }else if(c == 127){
                lcdCol--;
                if(lcdCol < 0){
                    lcdCol = 0;
                }
                lcd->setCursor(lcdCol, lcdRow);
                ret = lcd->print(' ');
                lcd->setCursor(lcdCol, lcdRow);
            }else{
                lcd->setCursor(lcdCol, lcdRow);
                ret = lcd->print(c);
                lcdCol++;
                if(lcdCol >= LCD_COLS){
                    lcdCol = 0;
                    lcdRow++;
                    if(lcdRow >= LCD_ROWS){
                        lcdRow = 0;
                    }
                }
            }
        }

        return ret == 1 ? 0 : -1;
    }

    void redirectStdout(){
        if(lcd == NULL){
            lcd = new LCD(LCD_ADDR, LCD_COLS, LCD_ROWS);
            lcd->begin();
        }

        if(!serialEnabled){
            Serial.begin(SERIAL_BAUD);
            serialEnabled = true;
        }

        _stdout = fdevopen(&putChar, NULL);
    }

    void stdoutToSerial(){
        serialPrint = true;
    }

    void stdoutToLCD(){
        serialPrint = false;
    }

    void stdinToSerial(){
        if(!serialEnabled)
            Serial.begin(SERIAL_BAUD);
        
        serialEnabled = true;

        _stdin = fdevopen(NULL, &getCharSerial);
    }

    void clearLCD(){
        lcd->clear();
        lcdRow = 0;
        lcdCol = 0;
    }
#endif

/*
    L298N.h
*/

class L298N{
    private:
        int in1;
        int in2;
        int en;
        int speed = 0;
        int targetSpeed = 0;
        int analogMap(int speed);
    public:
        L298N(int in1, int in2, int en);
        void setTargetSpeed(int speed);
        void setSpeed();
        void applySpeed();
        int getSpeed();
        int getTargetSpeed();
};

/*
    L298N.cpp
*/

L298N::L298N(int in1, int in2, int en){
    this->in1 = in1;
    this->in2 = in2;
    this->en = en;
    this->speed = 0;

    pinMode(this->in1, OUTPUT);
    pinMode(this->in2, OUTPUT);
    pinMode(this->en, OUTPUT);
}

void L298N::setTargetSpeed(int speed){
    if(speed > 100){
        this->targetSpeed = 100;
    }else if(speed < -100){
        this->targetSpeed = -100;
    }else{
        this->targetSpeed = speed;
    }
}

void L298N::setSpeed(){
    if(this->targetSpeed > this->speed){
        this->speed += SPEED_STEP;
    }else if(this->targetSpeed < this->speed){
        this->speed -= SPEED_STEP;
    }

    this->applySpeed();

    delay(10);
}

void L298N::applySpeed(){
    if(this->speed == 0){
        analogWrite(this->en, 0);
        digitalWrite(this->in1, LOW);
        digitalWrite(this->in2, LOW);
    }else if(this->speed > 0){
        analogWrite(this->en, this->analogMap(this->speed));
        digitalWrite(this->in1, HIGH);
        digitalWrite(this->in2, LOW);
    }else if(this->speed < 0){
        analogWrite(this->en, this->analogMap(this->speed));
        digitalWrite(this->in1, LOW);
        digitalWrite(this->in2, HIGH);
    }
}

int L298N::getSpeed(){
    return this->speed;
}

int L298N::analogMap(int speed){
    speed = abs(speed);

    return (int)map(speed, 0, 100, 0, 255);
}

int L298N::getTargetSpeed(){
    return this->targetSpeed;
}

/*
    Relay.h
*/

class Relay{
    private:
        int pin;
        bool state;
    public:
        Relay(int pin);
        void toggle();
        void setState(bool state);
        bool getState();
};

/*
    Relay.cpp
*/

Relay::Relay(int pin){
    this->pin = pin;
    this->state = false;
    pinMode(this->pin, OUTPUT);
}

void Relay::toggle(){
    this->state = !this->state;
    digitalWrite(this->pin, this->state);
}

void Relay::setState(bool state){
    this->state = state;
    digitalWrite(this->pin, this->state);
}

bool Relay::getState(){
    return this->state;
}

/*
    main.cpp
*/
#if TINKERCAD
    LCD lcd = LCD(LCD_ADDR, LCD_COLS, LCD_ROWS);
#endif

Relay relay(RELAY_IN);
L298N motor(MOTOR_IN1, MOTOR_IN2, MOTOR_EN);

String inputBuffer = "";

int getPercentage(String input){
    bool negative = false;

    if(input[input.length() - 1] != '%'){
        return -1;
    }

    if(input[0] == '-'){
        negative = true;
        input.remove(0, 1);
    }

    for(unsigned int i = 0; i < input.length() - 1; i++){
        if(input[i] < '0' || input[i] > '9'){
            return -1;
        }
    }

    int percentage = input.substring(0, input.length() - 1).toInt();

    return negative ? -percentage : percentage;
}

void setup(){
    #if !TINKERCAD
        stdinToSerial();
        redirectStdout();

        stdoutToLCD();
        clearLCD();
        printf("%d%%", motor.getSpeed());
    #else
        Serial.begin(SERIAL_BAUD);

        lcd.begin();
        lcd.print(motor.getSpeed());
        lcd.print("%");
    #endif
}

void loop(){
    if(motor.getSpeed() != motor.getTargetSpeed()){
        motor.setSpeed();

        #if !TINKERCAD
            stdoutToLCD();
            clearLCD();
            printf("%d%%", motor.getSpeed());
        #else
            lcd.clear();
            lcd.print(motor.getSpeed());
            lcd.print("%");
        #endif
    }

    #if !TINKERCAD
        char c = getchar();

        if(c){
            stdoutToSerial();

            if(c == 13){
                if(inputBuffer == "ON"){
                    relay.setState(true);
                }else if(inputBuffer == "OFF"){
                    relay.setState(false);
                }else{
                    if(getPercentage(inputBuffer) != -1){
                        motor.setTargetSpeed(getPercentage(inputBuffer));
                    }else if(inputBuffer.length() > 0){
                        printf("\nInvalid input: %s", inputBuffer.c_str());
                    }
                }

                inputBuffer = "";
            }else if(c == 127){
                if(inputBuffer.length() > 0)
                    inputBuffer.remove(inputBuffer.length() - 1);
            }else if(c == 8){
                if(inputBuffer.length() > 0)
                    inputBuffer.remove(inputBuffer.length() - 1);
                c = 127;
            }else if(c != 127 && c != 13 && c != 10 && c != 8){
                inputBuffer += c;
            }

            printf("%c", c);
        }
    #else
        inputBuffer = Serial.readStringUntil('\n');

        if(inputBuffer[inputBuffer.length() - 1] == 13){
            inputBuffer.remove(inputBuffer.length() - 1);
        }

        if (inputBuffer != ""){
            Serial.println(inputBuffer);

            if(inputBuffer == "ON"){
                relay.setState(true);
            }else if(inputBuffer == "OFF"){
                relay.setState(false);
            }else{
                int percentage = getPercentage(inputBuffer);
                if(percentage != -1){
                    motor.setTargetSpeed(percentage);
                }else if(inputBuffer.length() > 0){
                    Serial.print("Invalid input: ");
                    Serial.println(inputBuffer);
                }
            }

            inputBuffer = "";
        }
    #endif
}
