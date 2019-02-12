#ifndef CANSAT_UTILS
#define CANSAT_UTILS

void beginTransmission(int);
void endTransmission();
void endAllTransmissions();
void sendFloat(float);
void sendFloatAfter(char, float);

float readFloat();
float readFloatAfter(char);

#endif // CANSAT_UTILS