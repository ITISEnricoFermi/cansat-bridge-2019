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
  sendFloat('a', gps.pvt.lat);
  sendFloat('b', gps.pvt.lon);
  sendFloat('h', gps.pvt.height);
}

void sendFloat(char type, float number)
{
  Wire.beginTransmission(4);
  Wire.write(type);
  Wire.write((byte*)&number, sizeof(float));
  Wire.endTransmission(); 
}

#pragma region sperimentale

void sendDouble(char type, double number)
{
  Wire.beginTransmission(4);
  Wire.write(type);
  Wire.write((byte*)&number, sizeof(double));
  Wire.endTransmission(); 
}

#pragma endregion

void regulateLoop(float dt)
{
  static uint32_t prev_time = 0;
  uint32_t dT = int(dt*1000000);
  while((micros()-prev_time)<dT) {}
  prev_time = micros();
}
