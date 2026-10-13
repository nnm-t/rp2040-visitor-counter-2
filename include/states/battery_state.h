#pragma once

#include "tm1627.h"

#include "states/i_state.h"
#include "states/state_selector.h"

class BatteryState : public IState
{
    static constexpr const pin_size_t adc3_pin = 29;
    static constexpr const uint32_t state_ms = 3000;
    // 0-4095 to 0-3300 変換式 (1/3分圧対策済)
    static constexpr const int32_t battery_level_ratio = (uint32_t)(3.3f * 3 * 1000.0f / 4095.0f);

    StateSelector& _selector;
    TM1627& _tm1627;
    uint32_t _begin_ms = 0;

public:
    BatteryState(StateSelector& selector, TM1627& tm1627) : _selector(selector), _tm1627(tm1627)
    {

    }

    void begin() override;

    void update() override;
};