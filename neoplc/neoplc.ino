#include <Wire.h>
#include <String.h>
#include <neoENV.h>
#include <neoGPS.h>
#include <neoIMU.h> 
#include <ArduinoJson.h>

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

  StaticJsonBuffer<sizeof(double) * 12> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temp"] = temp;
  root["umid"] = humi;
  root["pres"] = pres;
  
  
  regulateLoop(1.0);
  
  Wire.beginTransmission(4);
  root.printTo(data);
  Serial.print("Data length: ");
  Serial.println(data.length());
  Wire.write(data.c_str(), data.length());
  Wire.endTransmission();  
}


void regulateLoop(float dt)
{
  static uint32_t prev_time = 0;
  uint32_t dT = int(dt*1000000);
  while((micros()-prev_time)<dT) {}
  prev_time = micros();
}
