/*
    Led class for Senior Design 2
    Spring 2021 by Ahmad El-Baba
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