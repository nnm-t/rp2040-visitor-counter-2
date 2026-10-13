#pragma once

#include "states/i_state.h"
#include "states/state_selector.h"

class MainState : public IState
{
    StateSelector& _selector;

public:
    MainState(StateSelector& selector) : _selector(selector)
    {

    }

    void begin() override;

    void update() override;
};