#include <Wire.h>
#include <LoRa.h>
#include <SPI.h>

union u_tag {
  byte b[sizeof(float)];
  float fval;
} u;

void setup()
{
    Wire.begin(4);
    Wire.onReceive(receiveEvent);
    if (!LoRa.begin(433E6)) {
      Serial.println("Starting LoRa failed!");
      while (1);
    }
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
      Serial.print("Temperatura: ");
      Serial.println(readFloat());
    }
    if (c == 'p') {
      Serial.print("Pressione: ");
      Serial.println(readFloat());
    }
    if (c == 'u') {
      Serial.print("Umidita': ");
      Serial.println(readFloat());
    }
    LoRa.beginPacket();
    bool ended = false;
    switch (c)
    {
        case 't':
            float localTemp = readFloat();
            LoRa.print("Temperatura: ");
            LoRa.print(localTemp);
            LoRa.println();
            LoRa.endPacket();
            ended = true;
            break;

            case 'p':
            float localPress = readFloat();
            LoRa.print("Pressione: ");
            LoRa.print(localPress);
            LoRa.println();
            LoRa.endPacket();
            ended = true;
            break;

            case 'u':
            float localHumi = readFloat();
            LoRa.print("Umidita: ";
            LoRa.print(localHumi);
            LoRa.println();
            LoRa.endPacket();
            ended = true;

        default:
            break;
    }
    if (!ended) {
        LoRa.endPacket();
    }
    
  }
}

float readFloat() {
  short i = 0;
  while (Wire.available() && i < sizeof(float)) {
    u.b[i++] = Wire.read();
  }
  return u.fval;
}