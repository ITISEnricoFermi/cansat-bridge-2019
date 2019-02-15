#ifndef CANSAT_UTILS
#define CANSAT_UTILS

namespace CansatUtils
{
void beginTransmission(int);
void endTransmission();
void endAllTransmissions();
void sendFloat(float);
void sendFloatAfter(char, float);

float lastFloat = 0;
float readFloat();
float readFloatAfter(char);

void printFloat(float var, int decimali);
void loraFloat(float var, int decimali);
} // namespace CansatUtils

#endif // CANSAT_UTILS