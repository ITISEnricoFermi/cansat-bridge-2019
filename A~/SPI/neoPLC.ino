#include <SPI.h>

char buffer[100];
volatile byte pos;
volatile boolean process_it;

void setup(void)
{
    Serial.begin(115200);
    SPCR |= bit(SPE);
    pinMode(MISO, OUTPUT);
    pos = 0;
    process_it = false;
    SPI.attachInterrupt();
}

ISR(SPI_STC_vect)
{
    byte c = SPDR;
    if (pos < (sizeof(buffer) - 1))
        buffer[pos++] = c;
    if (c == '\n')
        process_it = true;
}

void loop(void)
{
    if (process_it)
    {
        buffer[pos] = 0;
        Serial.println(buffer);
        pos = 0;
        process_it = false;
    }
}