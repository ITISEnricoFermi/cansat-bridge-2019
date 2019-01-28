#include <Wire.h>
#include <LoRa.h>
#include <SPI.h>
#include <SD.h>

union u_tag {
  byte b[sizeof(float)];
  float fval;
} u;

#pragma region sperimentale
union w_tag {
  byte b[sizeof(double)];
  double dval;
}w;

double readDouble()
{
   short i = 0;
    while (Wire.available() && i < sizeof(double))
    {
      w.b[i++] = Wire.read();
    }
    return w.dval;
}
#pragma endregion

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

  void logFile(float var, int type) //type 1:temp 2:press 3:humi 4:altezza
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
      case 'a':
      {
        float localTemp = readFloat();
        LoRa.print("Temperatura: ");
        LoRa.print(localTemp);
        LoRa.println();
        LoRa.endPacket();
        logFile(localTemp, 1);
        ended = true;
      }

      case 'b':
      {
        
        float localHumi = readFloat();
        LoRa.print("Umidita: ");
        LoRa.print(localHumi);
        LoRa.println();
        LoRa.endPacket();
        logFile(localHumi, 3);
        ended = true;
      }

      case 'c':
      {
        float localPress = readFloat();
        LoRa.print("Pressione: ");
        LoRa.print(localPress);
        LoRa.println();
        LoRa.endPacket();
        logFile(localPress, 2);
        ended = true;
      }

      case 'd':
      {
        double lat = readDouble();
        LoRa.print("Latitudine: ");
        LoRa.print(lat);
        LoRa.endPacket();
        logFile(lat, ); //metodo logFile serve type
        ended = true;
      }

      case 'e':
      {
        double lon = readDouble();
        LoRa.print("Latitudine: ");
        LoRa.print(lat);
        LoRa.endPacket();
        logFile(lon, ); //metodo logFile serve type
        ended = true;
      }

      case 'f':
      {
        float altezza = readFloat();
        LoRa.print("Altezza: ");
        LoRa.print(altezza);
        LoRa.println();
        LoRa.endPacket();
        logFile(altezza, 4);
        ended = true;
      }

      case 'g':
      {
        float ax = readFloat();
        LoRa.print("Accelerazione X: ");
        LoRa.print(ax);
        LoRa.println();
        LoRa.endPacket();
        logFile(ax, ); //metodo logFile serve type
        ended = true;
      }

      case 'h':
      {
        float ay = readFloat();
        LoRa.print("Accelerazione Y: ");
        LoRa.print(ay);
        LoRa.println();
        LoRa.endPacket();
        logFile(ay, ); //metodo logFile serve type
        ended = true;
      }

      case 'i':
      {
        float az = readFloat();
        LoRa.print("Accelerazione Z: ");
        LoRa.print(az);
        LoRa.println();
        LoRa.endPacket();
        logFile(az, ); //metodo logFile serve type
        ended = true;
      }

      case 'l':
      {
        float gx = readFloat();
        LoRa.print("Gravità X: ");
        LoRa.print(gx);
        LoRa.println();
        LoRa.endPacket();
        logFile(gx, ); //metodo logFile serve type
        ended = true;
      }

      case 'm':
      {
        float gy = readFloat();
        LoRa.print("Gravità Y: ");
        LoRa.print(gx);
        LoRa.println();
        LoRa.endPacket();
        logFile(gy, ); //metodo logFile serve type
        ended = true;
      }

      case 'n':
      {
        float gz = readFloat();
        LoRa.print("Gravità Z: ");
        LoRa.print(gz);
        LoRa.println();
        LoRa.endPacket();
        logFile(gz, ); //metodo logFile serve type
        ended = true;
      }

      case 'o':
      {
        float mx = readFloat();
        LoRa.print("Magnetismo X: ");
        LoRa.print(mx);
        LoRa.println();
        LoRa.endPacket();
        logFile(mx, ); //metodo logFile serve type
        ended = true;
      }

      case 'p':
      {
        float my = readFloat();
        LoRa.print("Magnetismo Y: ");
        LoRa.print(my);
        LoRa.println();
        LoRa.endPacket();
        logFile(my, ); //metodo logFile serve type
        ended = true;
      }

      case 'q':
      {
        float mz = readFloat();
        LoRa.print("Magnetismo Z: ");
        LoRa.print(mz);
        LoRa.println();
        LoRa.endPacket();
        logFile(mz, ); //metodo logFile serve type
        ended = true;
      }

      default:
        break;
      }
      if (!ended)
      {
        LoRa.endPacket();
      }
      ended = false;
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