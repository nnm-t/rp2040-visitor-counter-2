#include "led.h"

void LED::begin()
{
    pinMode(_pin, OUTPUT);
}

void LED::on()
{
    _pin_status = _gpio_mode == GPIOMode::Sink ? LOW : HIGH;
    digitalWrite(_pin, _pin_status);
}

void LED::off()
{
    _pin_status = _gpio_mode == GPIOMode::Sink ? HIGH : LOW;
    digitalWrite(_pin, _pin_status);
}

void LED::toggle()
{
    _pin_status = _pin_status ? LOW : HIGH;
    digitalWrite(_pin, _pin_status);
}