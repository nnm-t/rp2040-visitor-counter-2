#include "states/main_state.h"

void MainState::begin()
{

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
            _buzzer.beep(buzzer_frequency_hz, buzzer_duration_ms);

            // CSV出力
            if (write_csv_func != nullptr)
            {
                write_csv_func(SwitchNumber::Switch1);
            }
            break;
        case SwitchNumber::Switch2:
            _switch_press_ms = millis();
            // SW2押した直後
            _led_green.on();
            _buzzer.beep(buzzer_frequency_hz, buzzer_duration_ms);

            // CSV出力
            if (write_csv_func != nullptr)
            {
                write_csv_func(SwitchNumber::Switch2);
            }
            break;
        default:
            _pressed_switch = SwitchNumber::None;
            _led_red.off();
            _led_green.off();
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