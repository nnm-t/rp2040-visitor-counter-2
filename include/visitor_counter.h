#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include <RTClib.h>

#include "led.h"
#include "switch.h"
#include "switch_number.h"
#include "buzzer.h"

class VisitorCounter
{
    static constexpr const pin_size_t led_red_pin = 13;
    static constexpr const pin_size_t led_yellow_pin = 14;
    static constexpr const pin_size_t led_green_pin = 15;

    static constexpr const pin_size_t sw1_pin = 11;
    static constexpr const pin_size_t sw2_pin = 12;

    static constexpr const pin_size_t buzzer_pin = 10;

    static constexpr const pin_size_t i2c0_sda = 8;
    static constexpr const pin_size_t i2c0_scl = 9;

    static constexpr const pin_size_t spi0_clk = 2;
    static constexpr const pin_size_t spi0_mosi = 3;
    static constexpr const pin_size_t spi0_miso = 4;
    static constexpr const pin_size_t spi0_ss = 5;

    static constexpr const pin_size_t uart0_tx = 0;
    static constexpr const pin_size_t uart0_rx = 1;
    static constexpr const uint32_t uart_baud = 115200;

    static constexpr const size_t str_buffer_size = 128;

    static constexpr const uint32_t buzzer_frequency_hz = 2000;
    static constexpr const uint32_t buzzer_duration_ms = 50;

    static VisitorCounter* _instance;

    LED _led_red = LED(led_red_pin, GPIOMode::Sink);
    LED _led_yellow = LED(led_yellow_pin, GPIOMode::Sink);
    LED _led_green = LED(led_green_pin, GPIOMode::Sink);

    Switch _switch_1 = Switch(sw1_pin, INPUT_PULLUP);
    Switch _switch_2 = Switch(sw2_pin, INPUT_PULLUP);

    Buzzer _buzzer = Buzzer(buzzer_pin);

    File _file = File();

    RTC_PCF8563 _pcf8563 = RTC_PCF8563();

    char _str_buffer[str_buffer_size] = { 0 };
    size_t _str_current = 0;

    bool _is_rtc_configured = false;
    bool _is_csv_opened = false;

    bool _switch_1_pressed = false;
    bool _switch_2_pressed = false;
    uint32_t _switch_count = 0;

    uint32_t _power_count = 0;

    static void on_switch_1_pressed();

    static void on_switch_2_pressed();

    void read_serial();

    void init_sd();

    void init_gpio_interrupt();

    void write_csv(const SwitchNumber switch_number);

public:
    VisitorCounter()
    {
        _instance = this;
    }

    void begin();

    void update(const uint32_t delay_ms);
};