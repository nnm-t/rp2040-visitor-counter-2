#include "tm1627.h"

void TM1627::begin(const uint8_t intensity)
{
    _tm16xx.begin(true, intensity);
}

void TM1627::clearDisplay()
{
    _tm16xx.clearDisplay();
}

void TM1627::clearDisplayDigit(const uint8_t position)
{
    setSegments(segment_bit_empty, position);
}

void TM1627::setSegments(const uint8_t segments, const uint8_t position)
{
    if (position >= max_digit)
    {
        return;
    }

    // 桁とセグメントの指定を入れ替える
    for (uint8_t i = 0; i < max_segment; i++)
    {
        const bool is_segment_on = (segments >> i) & 0b00000001;
        _segments[i] = is_segment_on ? (_segments[i] | (0b00000001 << position)) : (_segments[i] & (0xFF - (0b00000001 << position)));

        _tm16xx.setSegments(_segments[i], i);
    }
}

void TM1627::setDisplayDigit(const uint8_t digit, const uint8_t position)
{
    if (digit >= max_segment_digit)
    {
        return;
    }

    setSegments(segment_bits[digit], position);
}

void TM1627::setDisplayMinus(const uint8_t position)
{
    setSegments(segment_bit_minus, position);
}

bool TM1627::setDisplay(const int32_t value, const uint8_t end_position)
{
    if (value > 9999 | value < -999)
    {
        return false;
    }

    bool show_minus = false;

    for (uint8_t i = 0; i < 4; i++)
    {
        const int32_t cardinal = std::pow(10, 1 + i);
        const int8_t position = end_position - i;

        if (position < 0)
        {
            break;
        }

        if (value / cardinal < 1)
        {
            if (value < 0 && !show_minus)
            {
                setDisplayMinus(position);
                show_minus = true;
            }

            clearDisplayDigit(end_position - i);
            continue;
        }

        setDisplayDigit(value % cardinal, position);
    }

    return true;
}