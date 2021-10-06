/*
    Led Class for Senior Design 2
    Spring 2021 by Ahmad El-Baba
*/

#include <Arduino.h>
#pragma once

using namespace std;

class Led
{
private:
    uint8_t _pin;
    bool state;

public:
    Led(uint8_t pin);
    void TurnOn();
    void TurnOff();
    void WriteState(bool state);
    void ToggleState();
};
