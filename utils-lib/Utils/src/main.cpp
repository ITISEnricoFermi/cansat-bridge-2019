#include <Arduino.h>
#include <Wire.h>
#include "cansat-utils.h"

void setup()
{
  Serial.begin(115200);
  Wire.begin(4);
  while (!Serial)
    ;
}

void loop()
{
  Serial.println("Ricevo...");
  Serial.println(readFloat());
}