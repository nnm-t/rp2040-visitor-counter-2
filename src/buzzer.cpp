#include "buzzer.h"

void Buzzer::begin()
{
    pinMode(_pin, OUTPUT);
}

void Buzzer::beep(const uint32_t frequency_hz, const uint32_t duration_ms)
{
    tone(_pin, frequency_hz, duration_ms);
}