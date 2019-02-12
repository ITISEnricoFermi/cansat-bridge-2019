#include <SPI.h>
#include <Wire.h>
#include <LoRa.h>
#include <SD.h>

float temp;
float pres;
float umi;
float altt;
double alt;
double lon;
double lat;
float ax;
float ay;
float az;
float gx;
float gy; 
float gz;
float mx;
float my;
float mz; 

#define SLAVE_PIN 3
const int chipSelect = 4;

SPISettings settings(2000000, MSBFIRST, SPI_MODE0); 
    
union u_tag 
{
  byte b[sizeof(float)];
  float fval;
} u;

float readFloat()
{
  short i = 0;
  while (Wire.available() && i < sizeof(float)) {
    u.b[i++] = Wire.read();
  }
  return u.fval;
}

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

void setup()
{
    Serial.begin(115200);

    Wire.begin(4);
    pinMode(chipSelect, OUTPUT);
    Wire.onReceive(receiveEvent);
      
    if (!LoRa.begin(433E6)) {
      Serial.println("Starting LoRa failed!");
    // while (1);
    }
    
   if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");

   }      
   Serial.println("card initialized.");
   File dataFile = SD.open("Cansat.txt", FILE_WRITE); 
}
void loop()
{
  delay(100);
}

void receiveEvent(int howMany) {
  while (0 < Wire.available()) {
    SPI.beginTransaction(settings);
    digitalWrite (chipSelect, LOW);
    
    char c = Wire.read();
    if (c == '\n') continue;
    File dataFile = SD.open("Cansat.txt", FILE_WRITE); 
    if (c == 'a') {
      Serial.print("Temperatura: ");
      temp = readFloat();
      Serial.println(temp);
      dataFile.println("Temperatura: ");
      dataFile.println(temp);
      dataFile.println("--");
      }

    if (c == 'c') {
      Serial.print("Pressione: ");
      pres = readFloat();
      Serial.println(pres);
      dataFile.println("Pressione: ");
      dataFile.println(pres);
      dataFile.println("--");
      }
    if (c == 'b') {
      Serial.print("Umidita': ");
      umi = readFloat();
      Serial.println(umi);
      dataFile.println("Umidità: ");
      dataFile.println(umi);
      dataFile.println("--");
    } 
    if (c == 'd'){
      Serial.print("Altezza: ");
      alt = readFloat();
      Serial.println(alt);
      dataFile.println("Altezza: ");
      dataFile.println(alt);
      dataFile.println("--");
     }
    if (c == 'p'){
      Serial.print("Latitudine: ");
      lat = readDouble();
      Serial.println(lat);
      dataFile.println("Latitudine: ");
      dataFile.println(lat);
      dataFile.println("--");
     }
    if ( c == 'q'){
      Serial.print("Longitudine: ");
      lon = readDouble();
      Serial.println(lon);
      dataFile.println("Longitudine: ");
      dataFile.println(lon);
      dataFile.println("--");
     }
   if ( c == 'e'){
      Serial.print("Acc. x: ");
      ax = readFloat();
      Serial.println(ax);
      dataFile.println("Acc. x: ");
      dataFile.println(ax);
      dataFile.println("--");
     }
         
    if ( c == 'f'){
      Serial.print("Acc. y: ");
      ay = readFloat();
      Serial.println(ay);
      dataFile.println("Acc. y: ");
      dataFile.println(ay);
      dataFile.println("--");
     }
    if ( c == 'g'){
      Serial.print("Acc. z: ");
      az = readFloat();
      Serial.println(az);
      dataFile.println("Acc. z: ");
      dataFile.println(az);
      dataFile.println("--");
     }
    if ( c == 'h'){
      Serial.print("Grav. x: ");
      gx = readFloat();
      Serial.println(gx);
      dataFile.println("Grav. x: ");
      dataFile.println(gx);
      dataFile.println("--");
     }
    if ( c == 'i'){
      Serial.print("Grav. y: ");
      gy = readFloat();
      Serial.println(gy);
      dataFile.println("Grav. y: ");
      dataFile.println(gy);
      dataFile.println("--");
     }
    if ( c == 'l'){
      Serial.print("Grav. z: ");
      gz = readFloat();
      Serial.println(gz);
      dataFile.println("Grav. z: ");
      dataFile.println(gz);
      dataFile.println("--");
     }
    if ( c == 'm'){
      Serial.print("Magn. x: ");
      mx = readFloat();
      Serial.println(mx);
      dataFile.println("Magn. x: ");
      dataFile.println(mx);
      dataFile.println("--");
     }
    if ( c == 'n'){
      Serial.print("Magn. y: ");
      my = readFloat();
      Serial.println(my);
      dataFile.println("Magn. y: ");
      dataFile.println(my);
      dataFile.println("--");
     }
    if ( c == 'o'){
      Serial.print("Magn. z: ");
      mz = readFloat();
      Serial.println(mz);
      dataFile.println("Magn. z: ");
      dataFile.println(mz);
      dataFile.println("--");
     } 
     if ( c == 'r'){
      Serial.print("AltezzaENV : ");
      altt = readFloat();
      Serial.println(altt);
      dataFile.println("AltezzaENV: ");
      dataFile.println(altt);
      dataFile.println("--");
     }  
     dataFile.close();
     delay(1000);   
  }
  digitalWrite (chipSelect, HIGH);
  SPI.endTransaction(); 
     
   
  
  SPI.beginTransaction(settings);
  digitalWrite (SLAVE_PIN, LOW);
  delay(100);
  
 LoRa.beginPacket();
 LoRa.print("Temp: ");
 LoRa.print(temp);
 LoRa.print("   ");
 LoRa.print("Press: ");
 LoRa.print(pres);
 LoRa.print("  ");
 LoRa.print("Umi: ");
 LoRa.print(umi);
 LoRa.print("Latitudine: ");
 LoRa.print(lat);
 LoRa.print("  ");
 LoRa.print("Longitudine: ");
 LoRa.print(lon);
 LoRa.print("  ");
 LoRa.print("Altezza: ");
 LoRa.print(alt);
 LoRa.endPacket();
 
 digitalWrite (SLAVE_PIN, HIGH);
 SPI.endTransaction();
}
