#pragma once

class IState
{
public:
    virtual void begin() = 0;

    virtual void update() = 0;

    virtual void on_switch_1_pressed()
    {

    }

    virtual void on_switch_2_pressed()
    {

    }

    virtual void on_switch_3_pressed()
    {

    }

    virtual void on_switch_4_pressed()
    {

    }

    virtual void on_switch_5_pressed()
    {

    }
};