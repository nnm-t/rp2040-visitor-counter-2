#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <RTClib.h>

#include "visitor_counter.h"

namespace {
    constexpr const uint32_t delay_ms = 10;

    VisitorCounter visitor_counter;
}

void setup()
{
    visitor_counter.begin();
}

void loop()
{
    visitor_counter.update(delay_ms);

    delay(delay_ms);
}
