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
    union u_tagd {
        uint8_t b[sizeof(float)];
        float fval;
    } ud;

    while (Wire.available())
    {
        Wire.readBytesUntil('\0', ud.b, sizeof(float));
    }

    return ud.fval;
}

float readFloatAfter(char initiator)
{
    if ((char)Wire.read() == initiator)
    {
        return readFloat();
    }

    return -1;
}