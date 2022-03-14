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

#endif