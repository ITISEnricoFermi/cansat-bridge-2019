#include <Wire.h>
#include <string.h>
#include <neoENV.h>
#include <neoGPS.h>
#include <neoIMU.h> 

neoENV env = neoENV();

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

  String data = "";
    
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
  
  Wire.beginTransmission(4);
  Wire.write(temp);
  Wire.endTransmission();
  Wire.beginTransmission(4);
  Wire.write(humi);
  Wire.endTransmission(); 
  Wire.write(pres);
  Wire.endTransmission();
  

}


void regulateLoop(float dt)
{
  static uint32_t prev_time = 0;
  uint32_t dT = int(dt*1000000);
  while((micros()-prev_time)<dT) {}
  prev_time = micros();
}