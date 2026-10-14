#pragma once

#include "states/i_state.h"

class StateSelector
{
    IState* _current = nullptr;

    void switch_state(IState* state);

public:
    IState* main_state = nullptr;
    IState* battery_state = nullptr;
    IState* adjust_state = nullptr;

    StateSelector()
    {

    }

    void begin();

    void update();

    void to_main_state();
    void to_battery_state();
    void to_adjust_state();

    void on_switch_1_pressed();
    void on_switch_2_pressed();
    void on_switch_3_pressed();
    void on_switch_4_pressed();
    void on_switch_5_pressed();
};