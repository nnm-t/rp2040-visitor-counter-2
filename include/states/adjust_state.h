#pragma once

#include <Arduino.h>

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

public:
    AdjustState(StateSelector& selector) : _selector(selector)
    {

    }

    void begin() override;

    void update() override;
};