/*
    An object oriented approach to a latched button
    Jan 2015, for the Arduino forum, by MattS-UK

    Compiled and tested on a Mega 2560 R3

    Modified by Ahmad El-Baba
*/

#include <Arduino.h>
#pragma once

using namespace std;

class Button
{
protected:
    uint8_t _pin;            //hardware pin number
    boolean _state;          //current pin state
    boolean _wasPressed;     //button latch
    uint16_t _startDebounce; //start of debounce time

public:
    uint16_t debounceMs; //period before button latches

    Button(uint8_t pin);
    void poll(uint16_t now);                         //call periodically to refresh the button state
    boolean wasPressed(void) { return _wasPressed; } //return the latch state
    boolean getState(void) { return _state; }        //return the latch state
    void reset(void);                                //reset the latch
};