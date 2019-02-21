#include <Wire.h>
#include <neoENV.h>
#include <neoGPS.h>
#include <neoIMU.h>
#include <neoOLED.h>
#include <stdio.h>

neoENV env = neoENV();
neoGPS gps = neoGPS();
neoOLED oled = neoOLED();
neoIMU imu = neoIMU();

void regulateLoop(float dt);
void sendFloat(char type, float number);

float envA[2];
float imuA[8];

void setup()
{
  Wire.begin();
  env.begin();
  bool success = imu.begin(4, 16, 250, 12, 20);
  imu.pollAll();
  regulateLoop(1.0);

  oled.begin();
  oled.setFont(System5x7);
  oled.clear();
  oled.setRow(2);
  oled.println("Setup");
  oled.setRow(3);
  oled.println("Completato");
}

void loop()
{
  envA[0] = env.readTemperature();
  envA[1] = env.readHumidity();
  envA[2] = env.readPressure();
  imuA[0] = imu.ax;
  imuA[1] = imu.ay;
  imuA[2] = imu.az;
  imuA[3] = imu.gx;
  imuA[4] = imu.gy;
  imuA[5] = imu.gz;
  imuA[6] = imu.mx;
  imuA[7] = imu.my;
  imuA[8] = imu.mz;

  sendFloat('a', env[0]); //t
  delay(40);
  sendFloat('b', env[1]); //h
  delay(40);
  sendFloat('c', env[2]); //p
  delay(40);
  sendDouble('d', gps.pvt.lat);
  delay(40);
  sendDouble('e', gps.pvt.lon);
  delay(40);
  sendFloat('f', gps.pvt.height);
  delay(40);
  sendFloat('g', imuA[0]); //ax
  delay(40);
  sendFloat('h', imuA[1]); //ay
  delay(40);
  sendFloat('i', imuA[2]); //az
  delay(40);                        //rip j,k
  sendFloat('l', imuA[3]); //gx
  delay(40);
  sendFloat('m', imuA[4]); //gy
  delay(40);
  sendFloat('n', imuA[5]); //gz
  delay(40);
  sendFloat('o', imuA[6]); //mx
  delay(40);
  sendFloat('p', imuA[7]); //my
  delay(40);
  sendFloat('q', imuA[8]); //mz
}

void sendFloat(char type, float number)
{
  Wire.beginTransmission(4);
  Wire.write(type);
  Wire.write((byte *)&number, sizeof(float));
  Wire.endTransmission();
}

#pragma region sperimentale

void sendDouble(char type, double number)
{
  Wire.beginTransmission(4);
  Wire.write(type);
  Wire.write((byte *)&number, sizeof(double)); //,8?
  Wire.endTransmission();
}

#pragma endregion

void regulateLoop(float dt)
{
  static uint32_t prev_time = 0;
  uint32_t dT = int(dt * 1000000);
  while ((micros() - prev_time) < dT)
  {
  }
  prev_time = micros();
}
