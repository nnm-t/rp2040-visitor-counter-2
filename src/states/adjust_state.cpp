#include "states/adjust_state.h"

void AdjustState::begin()
{
    _mode = AdjustMode::Years;

    const DateTime date_time = _pcf8563.now();
    _year = date_time.year();
    _month = date_time.month();
    _day = date_time.day();
    _hour = date_time.hour();
    _minute = date_time.minute();
}

void AdjustState::update()
{
    if (_is_adjust_finished)
    {
        // 設定反映
        DateTime date_time(_year, _month, _day, _hour, _minute);
        _pcf8563.adjust(date_time);

        _tm1627.clearDisplay();

        _is_adjust_finished = false;
        // to MainState
        _selector.to_main_state();
        return;
    }

    switch (_mode)
    {
        case AdjustMode::Months:
        case AdjustMode::Days:
            _tm1627.clearDisplayDigit(4, 7);
            break;
        case AdjustMode::Hours:
        case AdjustMode::Minutes:
            _tm1627.clearDisplayDigit(0, 3);
            break;
    }

    // 変更中の2桁をblink
    if (millis() % 500 < 250)
    {
        switch (_mode)
        {
            case AdjustMode::Years:
                _tm1627.clearDisplay();
                break;
            case AdjustMode::Months:
                _tm1627.clearDisplayDigit(0, 1);
                _tm1627.setDisplay(_day, 3, 2);
                break;
            case AdjustMode::Days:
                _tm1627.setDisplay(_month, 1, 2);
                _tm1627.clearDisplayDigit(2, 3);
                break;
            case AdjustMode::Hours:
                _tm1627.clearDisplayDigit(4, 5);
                _tm1627.setDisplay(_minute, 7, 2);
                break;
            case AdjustMode::Minutes:
                _tm1627.setDisplay(_hour, 5, 2);
                _tm1627.clearDisplayDigit(6, 7);
                _tm1627.clearDisplayDigit(7);
                break;
        }
        return;
    }


    // 点灯
    switch (_mode)
    {
        case AdjustMode::Years:
            // Year: 橙
            show_7seg(_year, LED7SegColor::Orange);
            break;
        case AdjustMode::Months:
        case AdjustMode::Days:
            // Month, Day: 赤
            show_7seg(_month * 100 + _day, LED7SegColor::Red);
            break;
        case AdjustMode::Hours:
        case AdjustMode::Minutes:
            // Hour, Minute: 緑
            show_7seg(_hour * 100 + _minute, LED7SegColor::Green);
            break;
    }

}

void AdjustState::show_7seg(const int32_t value, const LED7SegColor color)
{
    switch (color)
    {
        case LED7SegColor::Red:
            _tm1627.setDisplay(value, 3);
            break;
        case LED7SegColor::Green:
            _tm1627.setDisplay(value, 7);
            break;
        case LED7SegColor::Orange:
            _tm1627.setDisplay(value, 3);
            _tm1627.setDisplay(value, 7);
            break;
    }
}

void AdjustState::on_switch_3_pressed()
{
    // decrement
    switch (_mode)
    {
        case AdjustMode::Years:
            if (_year <= 2000)
            {
                break;
            }
            _year--;
            break;
        case AdjustMode::Months:
            if (_month <= 1)
            {
                break;
            }
            _month--;
            break;
        case AdjustMode::Days:
            if (_day <= 1)
            {
                break;
            }
            _day--;
            break;
        case AdjustMode::Hours:
            if (_hour <= 0)
            {
                break;
            }
            _hour--;
            break;
        case AdjustMode::Minutes:
            if (_minute <= 0)
            {
                break;
            }
            _minute--;
            break;
    }
}

void AdjustState::on_switch_4_pressed()
{
    // increment
    switch (_mode)
    {
        case AdjustMode::Years:
            if (_year >= 2099)
            {
                break;
            }
            _year++;
            break;
        case AdjustMode::Months:
            if (_month >= 12)
            {
                break;
            }
            _month++;
            break;
        case AdjustMode::Days:
            switch (_month)
            {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    if (_day < 31)
                    {
                        _day++;
                    }
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    if (_day < 30)
                    {
                        _day++;
                    }
                    break;
                case 2:
                    if (_year % 4 == 0 && _day < 29)
                    {
                        _day++;
                    }
                    else if (_day < 28)
                    {
                        _day++;
                    }
                    break;
            }
            break;
        case AdjustMode::Hours:
            if (_hour >= 23)
            {
                break;
            }
            _hour++;
            break;
        case AdjustMode::Minutes:
            if (_minute >= 59)
            {
                break;
            }
            _minute++;
            break;
    }
}

void AdjustState::on_switch_5_pressed()
{
    // Mode increment
    switch (_mode)
    {
        case AdjustMode::Years:
            _mode = AdjustMode::Months;
            break;
        case AdjustMode::Months:
            _mode = AdjustMode::Days;
            break;
        case AdjustMode::Days:
            _mode = AdjustMode::Hours;
            break;
        case AdjustMode::Hours:
            _mode = AdjustMode::Minutes;
            break;
        case AdjustMode::Minutes:
            // Adjust
            _is_adjust_finished = true;
            break;
    }
}