/**
 * @file Led.cpp
 * @author Ahmad El-baba (@8AE)
 * @brief 
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include "Led.h"

/**
 * @brief Construct a new Led:: Led object
 * 
 * @param pin 
 */
Led::Led(uint8_t pin)
{
    _pin = pin;
    state = false;
    pinMode(_pin, OUTPUT);

    digitalWrite(pin, state); //Off initial state
}

/**
 * @brief 
 * 
 */
void Led::TurnOff()
{
    state = false;
    digitalWrite(_pin, state); //Off initial state
}

/**
 * @brief 
 * 
 */
void Led::TurnOn()
{
    state = true;
    digitalWrite(_pin, state); //Off initial state
}

/**
 * @brief 
 * 
 * @param newState 
 */
void Led::WriteState(bool newState)
{
    state = newState;
    digitalWrite(_pin, state);
}

/**
 * @brief 
 * 
 */
void Led::ToggleState()
{
    state = !state;
    digitalWrite(_pin, state);
}