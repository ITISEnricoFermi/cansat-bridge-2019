#include <SPI.h>

void setup()
{
    digitalWrite(SS, HIGH);
    SPI.begin();
}

void loop()
{
  char c;
  digitalWrite(SS, LOW);
  for (const char * p = "Hello, world!\n" ; c = *p; p++)
  SPI.transfer (c);
}
