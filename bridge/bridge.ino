#include <SPI.h>
#include <Wire.h>
#include <LoRa.h>

union u_tag {
  byte b[sizeof(float)];
  float fval;
} u;

float readFloat() {
  short i = 0;
  while (Wire.available() && i < sizeof(float)) {
    u.b[i++] = Wire.read();
  }
  return u.fval;
}


void setup()
{
    Serial.begin(115200);
    while(!Serial){}

    Wire.begin(4);
    
    Wire.onReceive(receiveEvent);
      
    if (!LoRa.begin(433E6)) {
      Serial.println("Starting LoRa failed!");
      while (1);
    }

    Serial.println("Setup complete!");
}
void loop()
{
  delay(100);
}

void receiveEvent(int howMany) {
  while (0 < Wire.available()) {
    char c = Wire.read();
    if (c == '\n') continue;
    if (c == 't') {
      Serial.print("Temp: ");
      Serial.println(readFloat());
    }
  }        
}
