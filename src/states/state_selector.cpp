#include "states/state_selector.h"

void StateSelector::begin()
{
    _current = main_state;

    if (_current == nullptr)
    {
        return;
    }

    _current->begin();
}

void StateSelector::switch_state(IState* state)
{
    if (state == nullptr)
    {
        return;
    }

    _current = state;
    _current->begin();
}

void StateSelector::update()
{
    if (_current == nullptr)
    {
        return;
    }

    _current->update();
}

void StateSelector::to_main_state()
{
    switch_state(main_state);
}

void StateSelector::to_battery_state()
{
    switch_state(battery_state);
}

void StateSelector::to_adjust_state()
{
    switch_state(adjust_state);
}
