#include<Servo.h>
Servo s4;
Servo s2;
Servo s3;

const float MAX_SERVO_DEGREES = 90;
const float motor1Angle = 0;
const float motor2Angle = 120;
const float motor3Angle = 240;
float targetAngle = 90;

int encoderPin1 = 2;
int encoderPin2 = 3;
 
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
 
long lastencoderValue = 0;
 
int lastMSB = 0;
int lastLSB = 0;


void setup()
{
  pinMode(encoderPin1, INPUT_PULLUP);
  pinMode(encoderPin2, INPUT_PULLUP);
 
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);

  Serial.begin(115200);

  s4.attach(5);
  s2.attach(6);
  s3.attach(9);
}

void loop()
{
  float motor1Value = getWeightedValue(motor1Angle, targetAngle, MAX_SERVO_DEGREES);
  float motor2Value = getWeightedValue(motor2Angle, targetAngle, MAX_SERVO_DEGREES);
  float motor3Value = getWeightedValue(motor3Angle, targetAngle, MAX_SERVO_DEGREES);

  s2.write(motor1Value);
  s4.write(motor3Value);
  s3.write(motor2Value);

  Serial.println(encoderValue); 

  targetAngle = encoderValue * 5;
}

void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit
 
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
 
  lastEncoded = encoded; //store this value for next time
}

float getComponentX(float alpha)
{
  return cos(alpha * PI / 180);
}

float getComponentY(float alpha)
{
  return sin(alpha * PI / 180);
}

float getAngleRatioX(float alpha, float beta)
{
  return getComponentX(alpha) * getComponentX(beta);
}

float getAngleRatioY(float alpha, float beta)
{
  return getComponentY(alpha) * getComponentY(beta);
}

float getWeightedValue(float alpha, float beta, float value)
{
  float ratioX = getAngleRatioX(alpha, beta);
  float ratioY = getAngleRatioY(alpha, beta);
  float ratio = ratioX + ratioY;
  return ((ratio * value) + value) / 2;
}
