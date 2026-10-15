#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include <RTClib.h>
#include <TM16xxIC.h>

#include "led.h"
#include "switch.h"
#include "switch_number.h"
#include "buzzer.h"
#include "tm1627.h"

#include "states/state_selector.h"
#include "states/main_state.h"
#include "states/battery_state.h"
#include "states/adjust_state.h"

class VisitorCounter
{
    static constexpr const pin_size_t led_red_pin = 13;
    static constexpr const pin_size_t led_yellow_pin = 14;
    static constexpr const pin_size_t led_green_pin = 15;
    static constexpr const pin_size_t led_blue_pin = 19;
    
    static constexpr const pin_size_t tm1627_dio_pin = 16;
    static constexpr const pin_size_t tm1627_clk_pin = 17;
    static constexpr const pin_size_t tm1627_stb_pin = 18;

    static constexpr const pin_size_t sw1_pin = 11;
    static constexpr const pin_size_t sw2_pin = 12;
    static constexpr const pin_size_t sw3_pin = 20;
    static constexpr const pin_size_t sw4_pin = 21;
    static constexpr const pin_size_t sw5_pin = 22;

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

    static constexpr const uint32_t chattering_interval_ms = 250;

    static constexpr const size_t str_buffer_size = 128;

    static VisitorCounter* _instance;
    static uint32_t _last_pressed_ms;

    LED _led_red = LED(led_red_pin, GPIOMode::Sink);
    LED _led_yellow = LED(led_yellow_pin, GPIOMode::Sink);
    LED _led_green = LED(led_green_pin, GPIOMode::Sink);
    LED _led_blue = LED(led_blue_pin, GPIOMode::Sink);

    Switch _switch_1 = Switch(sw1_pin, INPUT_PULLUP);
    Switch _switch_2 = Switch(sw2_pin, INPUT_PULLUP);
    Switch _switch_3 = Switch(sw3_pin, INPUT_PULLUP);
    Switch _switch_4 = Switch(sw4_pin, INPUT_PULLUP);
    Switch _switch_5 = Switch(sw5_pin, INPUT_PULLUP);

    Buzzer _buzzer = Buzzer(buzzer_pin);

    File _file = File();

    RTC_PCF8563 _pcf8563 = RTC_PCF8563();
    TM16xxIC _tm16xx = TM16xxIC(IC_TM1627, tm1627_dio_pin, tm1627_clk_pin, tm1627_stb_pin);
    TM1627 _tm1627 = TM1627(_tm16xx);

    char _str_buffer[str_buffer_size] = { 0 };
    size_t _str_current = 0;

    StateSelector _state_selector = StateSelector();
    MainState _main_state = MainState(_state_selector, _led_red, _led_yellow, _led_green, _buzzer);
    BatteryState _battery_state = BatteryState(_state_selector, _tm1627);
    AdjustState _adjust_state = AdjustState(_state_selector, _pcf8563, _tm1627, _led_yellow);

    static bool anti_chattering();

    static void on_switch_1_pressed();
    static void on_switch_2_pressed();
    static void on_switch_3_pressed();
    static void on_switch_4_pressed();
    static void on_switch_5_pressed();

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