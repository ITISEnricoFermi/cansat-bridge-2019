#ifndef CANSAT_D_LOG
#define CANSAT_D_LOG

#include <Arduino.h>
#include <Wire.h>

// Synchronizing Header
#define MU 0xB5
#define BLOX 0x62

// Message Class
#define ACK 0x05

// Message ID
#define _ACK 0x01 // ACK
#define _NAK 0x00

class ArduinoI2CLogger
{

public:
  ArduinoI2CLogger(uint8_t addr = 0x4);
  void begin(uint32_t Rate);
  uint8_t poll();

  bool verbose = false;
  bool ackNak = false;

  void updateDX();

private:
  uint8_t address = 0x4;
  uint8_t encode(char c);
  uint8_t parse(char *buffer);
  void configMessageRate(uint8_t CL, uint8_t ID, uint8_t IsOn);
  void configDataRate(uint16_t Rate);
  void get(char Class, char ID);

  uint8_t waitForAckNack(uint32_t timeout = 100);
  void ubxReplaceChecksum(char *message, int mLength);
  void ubxChecksumAndSend(char *message, int mLength);
  bool confirmChecksum(char *message, int mLength);

  void printCharArray(char message[], uint32_t mLength);

  void parse_NAV_PVT(NAV_PVT x);
};

#endif