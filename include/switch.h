#pragma once

#include <Arduino.h>

class Switch
{
    const pin_size_t _pin;
    const PinMode _mode;

public:
    Switch(const pin_size_t pin, const PinMode mode) : _pin(pin), _mode(mode)
    {

    }

    void begin();

    void attach_interrupt(voidFuncPtr callback, const PinStatus pin_status);

    void detach_interrupt();

    const PinStatus read();
};