#include "cansat-utils.h"
#include <Wire.h>

void beginTransmission(int address)
{
    Wire.beginTransmission(address);
}

void endTransmission()
{
    Wire.endTransmission();
}

void endAllTransmissions()
{
    Wire.endTransmission(true);
}

void sendFloat(float number)
{
    Wire.write((uint8_t *)&number, sizeof(float));
    Wire.write('\0');
}

void sendFloatAfter(char a, float number)
{
    Wire.write(a);
    sendFloat(number);
}

float readFloat()
{
    float number = 0;
    Wire.readBytesUntil('\0', (uint8_t *)&number, sizeof(float));
    return number;
}

float readFloatAfter(char terminator)
{
    while (!Wire.available())
        ;
    if (Wire.read() == terminator)
    {
        return readFloat();
    }

    return -1;
}