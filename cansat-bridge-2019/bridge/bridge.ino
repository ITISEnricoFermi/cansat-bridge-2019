#include <SPI.h>
#include <Wire.h>
#include <LoRa.h>

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

void printFloat(float var,int decimali) {
  char out[50];
  dtostrf(var,2,decimali,out);
  Serial.print(out);
}

void loraFloat(float var,int decimali) {
  char out[50];
  dtostrf(var,2,decimali,out);
  LoRa.print(out);
}
    
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
      printFloat(lat,7);
      Serial.println();
     }
    if ( c == 'q'){
      Serial.print("Longitudine: ");
      lon = readFloat();
      printFloat(lon,7);
      Serial.println();
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
 loraFloat(lat,7);
 LoRa.print("  ");
 LoRa.print("Longitudine: ");
 loraFloat(lon,7);
 LoRa.print("  ");
 LoRa.print("Altezza: ");
 LoRa.print(alt);
 LoRa.print("Acc. x: ");
 LoRa.print(ax);
 LoRa.print("Acc. y: ");
 LoRa.print(ay);
 LoRa.print("Acc. z: ");
 LoRa.print(az);
 LoRa.print("Grav. x: ");
 LoRa.print(gx);
 LoRa.print("Grav. y: ");
 LoRa.print(gy);
 LoRa.print("Grav. z: ");
 LoRa.print(gz);
 LoRa.print("Magn. x: ");
 LoRa.print(mx);
 LoRa.print("Magn. y: ");
 LoRa.print(my);
 LoRa.print("Magn. z: ");
 LoRa.print(mz);
 LoRa.print("AltezzaENV: ");
 LoRa.print(altt);
 LoRa.endPacket();

}
