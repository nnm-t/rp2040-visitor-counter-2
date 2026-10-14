#pragma once

#include <functional>

#include <Arduino.h>

#include "led.h"
#include "buzzer.h"
#include "switch_number.h"

#include "states/i_state.h"
#include "states/state_selector.h"

class MainState : public IState
{
    static constexpr const uint32_t buzzer_frequency_hz = 2000;
    static constexpr const uint32_t buzzer_duration_ms = 50;

    StateSelector& _selector;
    LED& _led_red;
    LED& _led_green;
    Buzzer& _buzzer;

    uint32_t _switch_press_ms = 0;
    SwitchNumber _pressed_switch = SwitchNumber::None;


public:
    std::function<void(const SwitchNumber)> write_csv_func = nullptr;

    MainState(StateSelector& selector, LED& led_red, LED& led_green, Buzzer& buzzer) : _selector(selector), _led_red(led_red), _led_green(led_green), _buzzer(buzzer)
    {

    }

    void begin() override;

    void update() override;

    void on_switch_1_pressed() override;
    void on_switch_2_pressed() override;
    void on_switch_3_pressed() override;
};