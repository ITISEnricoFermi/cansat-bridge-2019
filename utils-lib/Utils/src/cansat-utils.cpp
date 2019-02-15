#include "cansat-utils.h"
#include <Wire.h>
#include <LoRa.h>

void CansatUtils::beginTransmission(int address)
{
    Wire.beginTransmission(address);
}

void CansatUtils::endTransmission()
{
    Wire.endTransmission();
}

void CansatUtils::endAllTransmissions()
{
    Wire.endTransmission(true);
}

void CansatUtils::sendFloat(float number)
{
    Wire.write((uint8_t *)&number, sizeof(float));
    Wire.write('\0');
}

void CansatUtils::sendFloatAfter(char a, float number)
{
    Wire.write(a);
    sendFloat(number);
}

float CansatUtils::readFloat()
{
    union u_tag {
        uint8_t b[sizeof(float)];
        float fval;
    } u;

    short i = 0;
    while (Wire.available() && i < sizeof(float))
    {
        u.b[i++] = Wire.read();
    }
    return u.fval;
}

float CansatUtils::readFloatAfter(char initiator)
{
    if ((char)Wire.read() == initiator)
    {
        lastFloat = readFloat();
    }
    return lastFloat;
}

void CansatUtils::printFloat(float var, int decimali)
{
    char out[50];
    dtostrf(var, 2, decimali, out);
    Serial.print(out);
}

void CansatUtils::loraFloat(float var, int decimali)
{
    char out[50];
    dtostrf(var, 2, decimali, out);
    LoRa.print(out);
}