#include <Wire.h>
#include <LoRa.h>
#include <SPI.h>
#include <SD.h>

union u_tag {
  byte b[sizeof(float)];
  float fval;
} u;

float initialCoord[1];
const int chipSelect = 4; //?

File dataFile = SD.open("log.txt", FILE_WRITE);

float readFloat()
  {
    short i = 0;
    while (Wire.available() && i < sizeof(float))
    {
      u.b[i++] = Wire.read();
    }
    return u.fval;
  }

  void log(float var, int type) //type 1:temp 2:press 3:humi 4:altezza
  {
    if (dataFile)
    {
      switch (type)
      {
      case 1:
        dataFile.print("Temperatura: ");
        dataFile.print(var);
        dataFile.println();
        break;

        case 2:
        dataFile.print("Pressione: ");
        dataFile.print(var);
        dataFile.println();
        break;

        case 3:
        dataFile.print("Umidità: ");
        dataFile.print(var);
        dataFile.println();
        break;

        case 4:
        dataFile.print("Altezza: ");
        dataFile.print(var);
        dataFile.println();
        break;

      default:
        break;
      }
    }
  }

void receiveEvent(int howMany)
  {
    while (0 < Wire.available())
    {
      char c = Wire.read();
      LoRa.beginPacket();
      bool ended = false;
      switch (c)
      {
      case 't':
      {
        float localTemp = readFloat();
        LoRa.print("Temperatura: ");
        LoRa.print(localTemp);
        LoRa.println();
        LoRa.endPacket();

        ended = true;
      }

      case 'p':
      {
        float localPress = readFloat();
        LoRa.print("Pressione: ");
        LoRa.print(localPress);
        LoRa.println();
        LoRa.endPacket();
        ended = true;
      }

      case 'u':
      {
        float localHumi = readFloat();
        LoRa.print("Umidita: ");
        LoRa.print(localHumi);
        LoRa.println();
        LoRa.endPacket();
        ended = true;
      }

      case 'g1':
      {
        //Latitudine
        //metodo per ricevere double
        //lora print
      }

      case 'g2':
      {
        //Latitudine
        //metodo per ricevere double
        //lora print
      }

      case 'g3':
      {
        float altezza = readFloat();
        LoRa.print("Altezza: ");
        LoRa.print(altezza);
        LoRa.println();
        LoRa.endPacket();
        ended = true;
      }

      default:
        break;
      }
      if (!ended)
      {
        LoRa.endPacket();
      }
    }
  }

void setup()
{
  Wire.begin(4);
  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  if (!SD.begin(chipSelect))
  {
    Serial.println("Card failed, or not present");
    while (1)
      ;
    Wire.onReceive(receiveEvent);
  }
}
  void loop()
  {
    delay(100);
  }