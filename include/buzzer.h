#pragma once

#include <Arduino.h>

class Buzzer
{
    const pin_size_t _pin;

public:
    Buzzer(const pin_size_t pin) : _pin(pin)
    {

    }

    void begin();

    void beep(const uint32_t frequency_hz, const uint32_t duration_ms);
};