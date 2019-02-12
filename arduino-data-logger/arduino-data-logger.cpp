#include "arduino-data-logger.h"

ArduinoI2CLogger::ArduinoI2CLogger(uint8_t addr = 0x4)
{
    this->address = addr;
}

void ArduinoI2CLogger::begin(uint32_t rate)
{
}

uint8_t ArduinoI2CLogger::poll()
{
}