#include <Wire.h>
#include <neoENV.h>
#include <neoGPS.h>
#include <neoIMU.h> 
#include <stdio.h>

neoENV env = neoENV();

void regulateLoop(float dt);
void sendFloat(char type, float number);

float temp;
float humi;
float pres;

void setup() 
{
  Wire.begin(); 
  env.begin();
  Serial.begin(115200);

  regulateLoop(1.0);


}

void loop() 
{ 
  temp = env.readTemperature();
  humi = env.readHumidity();
  pres = env.readPressure();
  Serial.print("Temp : ");
  Serial.println(temp);
  Serial.print("Humi : ");
  Serial.println(humi);
  Serial.print("Press : ");
  Serial.println(pres);
  
  regulateLoop(1.0);

  sendFloat('t', temp);
  sendFloat('h', humi);
  sendFloat('p', pres);
   
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
