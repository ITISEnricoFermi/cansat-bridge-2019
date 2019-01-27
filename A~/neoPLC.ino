#include <Wire.h>
#include <neoENV.h>
#include <neoGPS.h>
#include <neoIMU.h> 
#include <neoOLED.h>
#include <stdio.h>

neoENV env = neoENV();
neoGPS gps = neoGPS();
neoOLED oled = neoOLED();

void regulateLoop(float dt);
void sendFloat(char type, float number);

float temp, humi, pres;

void setup() {
  Wire.begin(); 
  env.begin();
  oled.begin();  
  oled.setFont(System5x7);
  oled.clear();
  regulateLoop(1.0);
  oled.setRow(2);
  oled.println("Setup");
  oled.setRow(3);
  oled.println("Completato");
}

void loop() {
  temp = env.readTemperature();
  humi = env.readHumidity();
  pres = env.readPressure();
  sendFloat('t', temp);
  sendFloat('h', humi);
  sendFloat('p', pres);
  sendFloat('g1', gps.pvt.lat);
  sendFloat('g2', gps.pvt.lon);
  sendFloat('g3', gps.pvt.alt);
}

void sendFloat(char type, float number)
{
  Wire.beginTransmission(4);
  Wire.write(type);
  Wire.write((byte*)&number, sizeof(float));
  Wire.endTransmission(); 
}

void regulateLoop(float dt)
{
  static uint32_t prev_time = 0;
  uint32_t dT = int(dt*1000000);
  while((micros()-prev_time)<dT) {}
  prev_time = micros();
}
