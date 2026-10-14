#pragma once

#include <Arduino.h>

#include "gpio_mode.h"

class LED
{
    const pin_size_t _pin;
    const GPIOMode _gpio_mode;
    uint8_t _pin_status = LOW;
    uint32_t _blink_on_ms = 0;
    uint32_t _blink_off_ms = 0;

public:
    LED(const pin_size_t pin, const GPIOMode gpio_mode) : _pin(pin), _gpio_mode(gpio_mode)
    {

    }

    void begin();

    void update();

    void on();

    void off();

    void toggle();

    void blink(const uint32_t on_ms, const uint32_t off_ms);
};