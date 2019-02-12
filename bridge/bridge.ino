#include <SPI.h>
#include <Wire.h>
#include <LoRa.h>
#include <stdio.h>
#include <stdarg.h>
//#include <cmath.h>
//funziona
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

float n = 10000;

void printFloat(float var, int decimali){
  char out[50];
  char out2[50];
  //var/=pow(10,decimali);
  dtostrf(var,4,decimali,out);
  sprintf(out2,"%s",out);
  Serial.println(out2);
}

#define SLAVE_PIN 3
const int chipSelect = 4;

SPISettings settings(2000000, MSBFIRST, SPI_MODE0); 
    
union u_tag 
{
  byte b[sizeof(float)];
  float fval;
} u;

union u_tagd
{
  byte b[sizeof(double)];
  double fval;
} ud;

float readFloat()
{
  short i = 0;
  while (Wire.available() && i < sizeof(float)) {
    u.b[i++] = Wire.read();
  }
  return u.fval;
}

double readDouble()
{
  short i = 0;
  while (Wire.available() && i < sizeof(double)) {
    ud.b[i++] = Wire.read();
  }
  return ud.fval;
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
  
}
void loop()
{
  delay(100);
}

void receiveEvent(int howMany) {
  while (0 < Wire.available()) {
    
    char c = Wire.read();
    if (c == '\n') continue;
    if (c == 'a') {
      Serial.print("Temperatura: ");
      temp = readFloat();
      Serial.println(temp);
      }

    if (c == 'c') {
      Serial.print("Pressione: ");
      pres = readFloat();
      Serial.println(pres);
      }
    if (c == 'b') {
      Serial.print("Umidita': ");
      umi = readFloat();
      Serial.println(umi);
    } 
    if (c == 'd'){
      Serial.print("Altezza: ");
      alt = readFloat();
      Serial.println(alt);
     }
    if (c == 'p'){
      Serial.print("Latitudine: ");
      lat = readFloat();
      Serial.println(lat);
     }
    if ( c == 'q'){
      Serial.print("Longitudine: ");
      lon =  readFloat()/10000000;
      Serial.println(lon);
     }
   if ( c == 'e'){
      Serial.print("Acc. x: ");
      ax = readFloat();
      Serial.println(ax);
     }
         
    if ( c == 'f'){
      Serial.print("Acc. y: ");
      ay = readFloat();
      Serial.println(ay);
     }
    if ( c == 'g'){
      Serial.print("Acc. z: ");
      az = readFloat();
      Serial.println(az);
     }
    if ( c == 'h'){
      Serial.print("Grav. x: ");
      gx = readFloat();
      Serial.println(gx);
     }
    if ( c == 'i'){
      Serial.print("Grav. y: ");
      gy = readFloat();
      Serial.println(gy);
     }
    if ( c == 'l'){
      Serial.print("Grav. z: ");
      gz = readFloat();
      Serial.println(gz);
     }
    if ( c == 'm'){
      Serial.print("Magn. x: ");
      mx = readFloat();
      Serial.println(mx);
     }
    if ( c == 'n'){
      Serial.print("Magn. y: ");
      my = readFloat();
      Serial.println(my);
     }
    if ( c == 'o'){
      Serial.print("Magn. z: ");
      mz = readFloat();
      Serial.println(mz);
     } 
     if ( c == 'r'){
      Serial.print("AltezzaENV : ");
      altt = readFloat();
      Serial.println(altt);
     }
     if ( c == 'k')
     {
        Serial.print("LON : ");
        lon = readFloat();
        Serial.println("lon float %d.%d");
       // (int)(lon*100)%100);
     }
     if ( c == 'x' ) {
      Serial.print("Var : ");
      int var = readFloat();
      int diff = 10000000 - var;
      //printFloat(var,7);
      Serial.print(var);
      Serial.println();
      Serial.print("Differenza : ");
      Serial.print(diff);
     }

  }

  
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

}
