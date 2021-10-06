/*
    Main IMS class for Senior Design 2
    Spring 2021 by Ahmad El-Baba
*/

#include <Arduino.h>

#include "IMS.h"

/**
 * @brief Construct a new IMS::IMS object
 * 
 * @param numberOfProfiles 
 */
IMS::IMS(uint8_t numberOfProfiles)
{
    _currentProfileIndex = 0;
    _state = false;

    amplitudeKnob = new DigiPot(18, 23, 24);
    fineAdjustmentKnob = new DigiPot(5, 15, 16);
    coarseKnob = new DigiPot(6, 7, 1);

    Serial.println("IMS has been made"); //DEBUG
}

/**
 * @brief Start
 * 
 */
void IMS::Start(void)
{
    Serial.println("IMS Start"); //DEBUG
    _state = true;

    amplitudeKnob->set(1);
    coarseKnob->set(1);
    fineAdjustmentKnob->set(1);
    //start timer
}

/**
 * @brief 
 * 
 */
void IMS::Stop(void)
{
    Serial.println("IMS Stop"); //DEBUG
    _state = false;

    amplitudeKnob->reset();
    coarseKnob->reset();
    fineAdjustmentKnob->reset();

    //stop timer
}

/**
 * @brief 
 * 
 * @param index 
 */
void IMS::SelectProfile(uint8_t index)
{
    _currentProfileIndex = index;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t IMS::GetNextProfile()
{
    if (_currentProfileIndex > 3)
    {
        _currentProfileIndex = 0;
    }
    else
    {
        _currentProfileIndex++;
    }
    return _currentProfileIndex;
}
