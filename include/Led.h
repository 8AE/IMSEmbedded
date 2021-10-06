/**
 * @file Led.h
 * @author Ahmad El-baba (@8AE)
 * @brief 
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
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
