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
} w;

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

void logFile(float var, int type)
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

    case 5:
      dataFile.print("Latitudine: ");
      dataFile.print(var);
      dataFile.println();
      break;

    case 6:
      dataFile.print("Longitudine: ");
      dataFile.print(var);
      dataFile.println();
      break;

    case 7:
      dataFile.print("Accelerazione X: ");
      dataFile.print(var);
      dataFile.println();
      break;

    case 8:
      dataFile.print("Accelerazione Y: ");
      dataFile.print(var);
      dataFile.println();
      break;

    case 9:
      dataFile.print("Accelerazione Z: ");
      dataFile.print(var);
      dataFile.println();
      break;

    case 10:
      dataFile.print("Gravità X: ");
      dataFile.print(var);
      dataFile.println();
      break;

    case 11:
      dataFile.print("Gravità Y: ");
      dataFile.print(var);
      dataFile.println();
      break;

    case 12:
      dataFile.print("Gravità Z: ");
      dataFile.print(var);
      dataFile.println();
      break;

    case 13:
      dataFile.print("Magnetismo X: ");
      dataFile.print(var);
      dataFile.println();
      break;

    case 14:
      dataFile.print("Magnetismo Y: ");
      dataFile.print(var);
      dataFile.println();
      break;

    case 15:
      dataFile.print("Magnetismo Z: ");
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
      Serial.print("Temperatura: ");
      Serial.print(localTemp); //debug
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
      Serial.print("Umidita: ");
      Serial.print(localHumi); //debug
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
      Serial.print("Pressione: ");
      Serial.print(localPress); //debug
    }

    case 'd':
    {
      double lat = readDouble();
      LoRa.print("Latitudine: ");
      LoRa.print(lat);
      LoRa.endPacket();
      logFile(lat, 5);
      ended = true;
      Serial.print("Latitudine: ");
      Serial.print(lat); //debug
    }

    case 'e':
    {
      double lon = readDouble();
      LoRa.print("Longitudine: ");
      LoRa.print(lon);
      LoRa.endPacket();
      logFile(lon, 6);
      ended = true;
      Serial.print("Longitudine: ");
      Serial.print(lon); //debug
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
      Serial.print("Altezza: ");
      Serial.print(altezza); //debug
    }

    case 'g':
    {
      float ax = readFloat();
      LoRa.print("Accelerazione X: ");
      LoRa.print(ax);
      LoRa.println();
      LoRa.endPacket();
      logFile(ax, 7);
      ended = true;
      Serial.print("Accelerazione X: ");
      Serial.print(ax); //debug
    }

    case 'h':
    {
      float ay = readFloat();
      LoRa.print("Accelerazione Y: ");
      LoRa.print(ay);
      LoRa.println();
      LoRa.endPacket();
      logFile(ay, 8);
      ended = true;
      Serial.print("Accelerazione Y: ");
      Serial.print(ay); //debug
    }

    case 'i':
    {
      float az = readFloat();
      LoRa.print("Accelerazione Z: ");
      LoRa.print(az);
      LoRa.println();
      LoRa.endPacket();
      logFile(az, 9);
      ended = true;
      Serial.print("Accelerazione Z: ");
      Serial.print(az); //debug
    }

    case 'l':
    {
      float gx = readFloat();
      LoRa.print("Gravità X: ");
      LoRa.print(gx);
      LoRa.println();
      LoRa.endPacket();
      logFile(gx, 10);
      ended = true;
      Serial.print("Gravità X: ");
      Serial.print(gx); //debug
    }

    case 'm':
    {
      float gy = readFloat();
      LoRa.print("Gravità Y: ");
      LoRa.print(gy);
      LoRa.println();
      LoRa.endPacket();
      logFile(gy, 11);
      ended = true;
      Serial.print("Gravità Y: ");
      Serial.print(gy); //debug
    }

    case 'n':
    {
      float gz = readFloat();
      LoRa.print("Gravità Z: ");
      LoRa.print(gz);
      LoRa.println();
      LoRa.endPacket();
      logFile(gz, 12);
      ended = true;
      Serial.print("Gravità Z: ");
      Serial.print(gz); //debug
    }

    case 'o':
    {
      float mx = readFloat();
      LoRa.print("Magnetismo X: ");
      LoRa.print(mx);
      LoRa.println();
      LoRa.endPacket();
      logFile(mx, 13);
      ended = true;
      Serial.print("Magnetismo X: ");
      Serial.print(mx); //debug
    }

    case 'p':
    {
      float my = readFloat();
      LoRa.print("Magnetismo Y: ");
      LoRa.print(my);
      LoRa.println();
      LoRa.endPacket();
      logFile(my, 14);
      ended = true;
      Serial.print("Magnetismo Y: ");
      Serial.print(my); //debug
    }

    case 'q':
    {
      float mz = readFloat();
      LoRa.print("Magnetismo Z: ");
      LoRa.print(mz);
      LoRa.println();
      LoRa.endPacket();
      logFile(mz, 15);
      ended = true;
      Serial.print("Magnetismo Z: ");
      Serial.print(mz); //debug
    }

    default:
      break;
    }
    if (!ended)
    {
      LoRa.endPacket();
    }
    else
    {
      ended = false;
    }
    Serial.println();
  }
}

void setup()
{
  Serial.begin(9600); //debug
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
  Serial.println("Setup Completato"); //debug
}
void loop()
{
  delay(100);
}