#pragma once

#include <Arduino.h>
#include <SD.h>

#include <ArduinoJson.h>
#include <RTClib.h>

#include "tm1627.h"
#include "switch_number.h"

class Counter
{
    RTC_PCF8563& _pcf8563;
    TM1627& _tm1627;

    char _file_name[24] = { 0 };

    uint32_t _switch_1 = 0;
    uint32_t _switch_2 = 0;

public:
    Counter(RTC_PCF8563& pcf8563, TM1627& tm1627) : _pcf8563(pcf8563), _tm1627(tm1627)
    {

    }

    void increment(const SwitchNumber switch_number);

    void clear_7seg();

    void read_json();
    void write_json();
};