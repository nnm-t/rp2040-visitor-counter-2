#pragma once

#include <Arduino.h>
#include <RTClib.h>

#include "tm1627.h"
#include "led.h"
#include "led_7seg_color.h"
#include "states/i_state.h"
#include "states/state_selector.h"

enum class AdjustMode : uint8_t
{
    Years = 0x00,
    Months = 0x01,
    Days = 0x02,
    Hours = 0x03,
    Minutes = 0x04
};

class AdjustState : public IState
{
    StateSelector& _selector;
    RTC_PCF8563& _pcf8563;
    TM1627& _tm1627;
    LED& _led_yellow;

    AdjustMode _mode = AdjustMode::Years;
    uint16_t _year = 0;
    uint8_t _month = 0;
    uint8_t _day = 0;
    uint8_t _hour = 0;
    uint8_t _minute = 0;

    bool _is_adjust_finished = false;

    void show_7seg(const int32_t value, const LED7SegColor color);

public:
    AdjustState(StateSelector& selector, RTC_PCF8563& pcf8563, TM1627& tm1627, LED& led_yellow) : _selector(selector), _pcf8563(pcf8563), _tm1627(tm1627), _led_yellow(led_yellow)
    {

    }

    void begin() override;

    void update() override;

    void on_switch_3_pressed() override;

    void on_switch_4_pressed() override;

    void on_switch_5_pressed() override;
};