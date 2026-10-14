#include "led.h"

void LED::begin()
{
    pinMode(_pin, OUTPUT);
}

void LED::update()
{
    if (_blink_on_ms == 0 || _blink_off_ms == 0)
    {
        return;
    }

    if (millis() % (_blink_on_ms + _blink_off_ms) < _blink_on_ms)
    {
        // on
        _pin_status = _gpio_mode == GPIOMode::Sink ? LOW : HIGH;
        digitalWrite(_pin, _pin_status);
        return;
    }

    // off
    _pin_status = _gpio_mode == GPIOMode::Sink ? HIGH : LOW;
    digitalWrite(_pin, _pin_status);
}

void LED::on()
{
    _blink_on_ms = 0;
    _blink_off_ms = 0;

    _pin_status = _gpio_mode == GPIOMode::Sink ? LOW : HIGH;
    digitalWrite(_pin, _pin_status);
}

void LED::off()
{
    _blink_on_ms = 0;
    _blink_off_ms = 0;

    _pin_status = _gpio_mode == GPIOMode::Sink ? HIGH : LOW;
    digitalWrite(_pin, _pin_status);
}

void LED::toggle()
{
    _blink_on_ms = 0;
    _blink_off_ms = 0;

    _pin_status = _pin_status ? LOW : HIGH;
    digitalWrite(_pin, _pin_status);
}

void LED::blink(const uint32_t on_ms, const uint32_t off_ms)
{
    _blink_on_ms = on_ms;
    _blink_off_ms = off_ms;
}