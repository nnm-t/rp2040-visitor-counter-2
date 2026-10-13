#include "states/battery_state.h"

void BatteryState::begin()
{
    _begin_ms = millis();
    // ADC3 (GPIO29)
    // 12bit (0-4095): 1/3分圧
    const int32_t battery_raw_level = analogRead(adc3_pin);
    const int32_t battery_level = battery_raw_level * battery_level_ratio;

    _tm1627.setDisplay(battery_level, 3);
}

void BatteryState::update()
{
    if (millis() > _begin_ms + state_ms)
    {
        _tm1627.clearDisplay();
        // MainStateへ戻る
        _selector.to_main_state();
    }
}