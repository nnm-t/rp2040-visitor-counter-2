#pragma once

#include <Arduino.h>

#include "gpio_mode.h"

class LED
{
    const pin_size_t _pin;
    const GPIOMode _gpio_mode;
    uint8_t _pin_status = LOW;

public:
    LED(const pin_size_t pin, const GPIOMode gpio_mode) : _pin(pin), _gpio_mode(gpio_mode)
    {

    }

    void begin();

    void on();

    void off();

    void toggle();
};