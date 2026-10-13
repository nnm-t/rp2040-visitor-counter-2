#pragma once

#include <cmath>

#include <Arduino.h>
#include <TM16xxIC.h>

class TM1627
{
    static constexpr const uint8_t max_segment = 8;
    static constexpr const uint8_t max_digit = 8;
    static constexpr const uint8_t max_segment_digit = 16;

    static constexpr const uint8_t segment_bits[max_segment_digit] = {
        0b00111111, // 0
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111, // 7
        0b01111111, // 8
        0b01101111, // 9
        0b01011111, // a
        0b01111100, // b
        0b00111001, // c
        0b01011110, // d
        0b01111011, // e
        0b01110001, // f
    };
    static constexpr const uint8_t segment_bit_minus = 0b01000000;
    static constexpr const uint8_t segment_bit_empty = 0b00000000;

    uint8_t _segments[max_digit] = { 0 };

    TM16xxIC& _tm16xx;

public:
    TM1627(TM16xxIC& tm16xx) : _tm16xx(tm16xx)
    {

    }

    void begin(const uint8_t intensity = 7);

    void clearDisplay();
    void clearDisplayDigit(const uint8_t position);

    void setSegments(const uint8_t segments, const uint8_t position);
    void setDisplayDigit(const uint8_t digit, const uint8_t position);
    void setDisplayMinus(const uint8_t position);
    bool setDisplay(const int32_t value, const uint8_t end_position);
};