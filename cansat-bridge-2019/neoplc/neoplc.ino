#include <Wire.h>
#include <neoOLED.h>
#include <neoENV.h>
#include <neoGPS.h>
#include <neoIMU.h> 
#include <stdio.h>
#include <neoBLE.h>

bool gps2;
bool env2;
bool imu2;

neoENV env = neoENV();
neoGPS gps = neoGPS();
neoIMU imu = neoIMU();
neoOLED oled = neoOLED();


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
  oled.begin();  
  oled.setFont(font8x8);
  oled.clear();
  Serial.begin(115200);
  regulateLoop(1.0);
  BLE.begin();
}

void loop() 
{ 
  oled.clear();
  oled.clearToEOL();
  
  if (temp && humi && pres && alt != 0 )
  {
  env2 = true;
  }
  if (!env2)
  {
    oled.setRow(2);
    oled.println("ENV !?"); 
  }
  if (env2)
  {
    oled.setRow(2);
    oled.println("ENV ok");
  }

  if (imu.ax && imu.ay && imu.az && imu.gx && imu.gy && imu.gz && imu.mx && imu.my && imu.mz != 0)
  {
    imu2 = true;
  }
  if (!imu2)
  {
    oled.setRow(3);
    oled.println("IMU !?");
  }
  if (imu2)
  {
    oled.setRow(3);
    oled.println("IMU ok");
  }

  
  if (gps.pvt.height && gps.pvt.lat && gps.pvt.lon != 0)
  {
    gps2 = true;
  }
  if (!gps2)
  {
    oled.setRow(4);
    oled.println("GPS !?");
  }
  if (gps2)
  {
    oled.setRow(4);
    oled.println("GPS ok");
  }

  
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
  copyToApp(); 
  
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

  
  sendFloat('p', gps.pvt.lat);
  sendFloat('q', gps.pvt.lon);

   
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
void copyToApp()
{
  for (int i=0; i<24; i++){
    oled.updateDX(i);
    BLE.post(oled.DX.raw);
    delay(10);
    }
  }
