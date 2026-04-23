#include "switch.h"

void Switch::begin()
{
    pinMode(_pin, _mode);
}

void Switch::attach_interrupt(voidFuncPtr callback, const PinStatus pin_status)
{
    attachInterrupt(_pin, callback, pin_status);
}

void Switch::detach_interrupt()
{
    detachInterrupt(_pin);
}

const PinStatus Switch::read()
{
    return digitalRead(_pin);
}