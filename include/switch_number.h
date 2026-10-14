#pragma once

#include <Arduino.h>

enum class SwitchNumber : uint8_t
{
    None = 0x00,
    Switch1 = 0x01,
    Switch2 = 0x02
};