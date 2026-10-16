#include "states/main_state.h"

void MainState::begin()
{
    _led_yellow.blink(50, 2950);
}

void MainState::update()
{
    if (millis() < _switch_press_ms + 1000)
    {
        return;
    }

    switch (_pressed_switch)
    {
        case SwitchNumber::Switch1:
            _switch_press_ms = millis();
            // SW1押した直後
            _led_red.on();
            _counter.increment(SwitchNumber::Switch1);
            _buzzer.beep(buzzer_frequency_hz, buzzer_duration_ms);

            // JSON書込, CSV出力
            if (pressed_func != nullptr)
            {
                pressed_func(SwitchNumber::Switch1);
            }

            _pressed_switch = SwitchNumber::None;
            break;
        case SwitchNumber::Switch2:
            _switch_press_ms = millis();
            // SW2押した直後
            _led_green.on();
            _counter.increment(SwitchNumber::Switch2);
            _buzzer.beep(buzzer_frequency_hz, buzzer_duration_ms);

            // JSON書込, CSV出力
            if (pressed_func != nullptr)
            {
                pressed_func(SwitchNumber::Switch2);
            }

            _pressed_switch = SwitchNumber::None;
            break;
        default:
            _led_red.off();
            _led_green.off();
            _counter.clear_7seg();
            break;
    }
}

void MainState::on_switch_1_pressed()
{
    _pressed_switch = SwitchNumber::Switch1;
}

void MainState::on_switch_2_pressed()
{
    _pressed_switch = SwitchNumber::Switch2;
}

void MainState::on_switch_3_pressed()
{
    _selector.to_battery_state();
}

void MainState::on_switch_5_pressed()
{
    _selector.to_adjust_state();
}