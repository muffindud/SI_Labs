#include "LCD.h"
#include "Wire.h"

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
