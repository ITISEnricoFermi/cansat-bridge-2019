#include <Wire.h>
#include <neoENV.h>
#include <neoGPS.h>
#include <neoIMU.h> 
#include <stdio.h>
#include <neoBLE.h>

neoENV env = neoENV();
neoGPS gps = neoGPS();
neoIMU imu = neoIMU();


void regulateLoop(float dt);

void sendFloat(char type, float number);

void sendDouble(char type, double number);



float temp;
float humi;
float pres;
float alt;
float ax;
float ay;
float az;
float gx;
float gy; 
float gz;
float mx;
float my;
float mz; 

void setup() 
{
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  Wire.begin(); 
  env.begin();
  BLE.begin();
  gps.verbose = false;
  gps.begin(1000);
  imu.begin(4,16,250,12,20);
  Serial.begin(115200);
  regulateLoop(1.0);
  Serial.print("c");
  BLE.begin();
}

void loop() 
{ 
  gps.poll();
  imu.pollAll();
  
  temp = env.readTemperature();
  humi = env.readHumidity();
  pres = env.readPressure();
  alt = env.readAltitude();
  
  Serial.print("Temp : ");
  Serial.println(temp);
  Serial.print("Humi : ");
  Serial.println(humi);
  Serial.print("Press : ");
  Serial.println(pres);
  Serial.print("Altezza : ");
  Serial.println(gps.pvt.height);
  Serial.print("Latitudine : ");
  Serial.println(gps.pvt.lat);
  Serial.print("Longitudine : ");
  Serial.println(gps.pvt.lon);
  Serial.print("ax = ");  
  Serial.print(imu.ax,4);  
  Serial.print("\tay = ");
  Serial.print(imu.ay,4); 
  Serial.print("\taz = ");
  Serial.print(imu.az,4);
  Serial.println(" g");
  Serial.print("gx = ");
  Serial.print(imu.gx,4);  
  Serial.print("\tgy = ");
  Serial.print(imu.gy,4); 
  Serial.print("\tgz = ");
  Serial.print(imu.gz,4);
  Serial.println(" deg/s");
  Serial.print("mx = ");     
  Serial.print(imu.mx,4);  
  Serial.print("\tmy = ");
  Serial.print(imu.my,4); 
  Serial.print("\tmz = ");
  Serial.print(imu.mz,4);
  Serial.println(" mG\n");
  
  BLE.post(gps.DXa.raw); 
  BLE.post(gps.DXb.raw);
  BLE.post(imu.DX.raw);
  BLE.post(env.DX.raw);
  
  regulateLoop(1.0);

  sendFloat('a', temp);
  sendFloat('b', humi);
  sendFloat('c', pres);
  sendFloat('d', gps.pvt.height);
  sendFloat('e' , imu.ax);
  sendFloat('f' , imu.ay);
  sendFloat('g' , imu.az);
  sendFloat('h' , imu.gx);
  sendFloat('i' , imu.gy);
  sendFloat('l' , imu.gz); 
  sendFloat('m' , imu.mx);
  sendFloat('n' , imu.my);     
  sendFloat('o' , imu.mz);  
  sendFloat('r' , alt);

  
  sendDouble('p', gps.pvt.lat);
  sendDouble('q', gps.pvt.lon);

   
}

void sendFloat(char type, float number)
{
  Wire.beginTransmission(4);
  Wire.write(type);
  Wire.write((byte*)&number, sizeof(float));
  Wire.endTransmission(); 
}

void sendDouble(char type, double number)
{
  Wire.beginTransmission(4);
  Wire.write(type);
  Wire.write((byte*)&number, sizeof(double));
  Wire.endTransmission(); 
}

void regulateLoop(float dt)
{
  static uint32_t prev_time = 0;
  uint32_t dT = int(dt*1000000);
  while((micros()-prev_time)<dT) {}
  prev_time = micros();
}
