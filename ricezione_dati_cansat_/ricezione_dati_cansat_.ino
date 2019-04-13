#include <SPI.h>
#include <LoRa.h>

int blink = 2;

void setup() 
{
  Serial.begin(9600);
  
  pinMode(blink,OUTPUT);
  
  if (!LoRa.begin(433E6))
  {
    Serial.println("Lora non trovato o funzionante !!!");
  }
}

void loop()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
  {
    while (LoRa.available()) 
    {
      Serial.print((char)LoRa.read());
      digitalWrite(blink,HIGH);
    }
    digitalWrite(blink,LOW);
  }
}
