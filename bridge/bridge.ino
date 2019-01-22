#include <SPI.h>
#include <Wire.h>
#include <LoRa.h>
//#include <ArduinoJson.h>

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
  while (1 < Wire.available()) { 
    char c = Wire.read(); 
    Serial.print(c);
  }        
  Serial.println();
}
