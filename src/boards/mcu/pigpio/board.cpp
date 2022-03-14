#if defined TARGET_PIGPIO
#include "boards/mcu/board.h"
#include <pigpio.h>


// Arduino API compatibility functions

void pinMode(uint8_t pin, uint8_t mode)
{
    unsigned pimode = 0;
    if (mode == INPUT) pimode = PI_INPUT;
    if (mode == OUTPUT) pimode = PI_OUTPUT;
    gpioSetMode(pin, pimode);
}

int digitalRead(uint8_t pin)
{
    return gpioRead(pin);
}

void digitalWrite(uint8_t pin, uint8_t val)
{
    gpioWrite(pin, val);
}

void delay(uint32_t ms)
{
    int seconds = ms / 1000;
    int micros = (ms % 1000) * 1000;
    gpioSleep(PI_TIME_RELATIVE, seconds, micros);
}

unsigned long millis(void)
{
    // gpioTick() cannot be used here, since it returns a uint32_t value of
    // microseconds, which wraps around too soon to be useful. Dividing by
    // 1000 its result would result in a wraparound at 4294967, way below
    // 2^32, which will throw off calculations at the wraparound time.
    int sec = 0; int usec = 0;
    gpioTime(PI_TIME_ABSOLUTE, &sec, &usec); // PI_TIME_ABSOLUTE saves one subtraction
    return (unsigned long)(usec / 1000) + ((unsigned long)sec * 1000);
}

#endif