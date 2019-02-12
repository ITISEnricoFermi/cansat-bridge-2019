#include <Arduino.h>
#include <Wire.h>
#include "cansat-utils.h"

void setup()
{
  Serial.begin(115200);
  Wire.begin(4);
  while (!Serial)
    ;
  Serial.println(readFloatAfter('t'));
}

void loop()
{
}