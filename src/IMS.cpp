/**
 * @file Ims.cpp
 * @author Ahmad El-baba (@8AE)
 * @brief 
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include "IMS.h"

/**
 * @brief Construct a new IMS::IMS object
 * 
 * @param numberOfProfiles 
 */
IMS::IMS(uint8_t numberOfProfiles, TimerObject *muscleTimer)
{
    const uint8_t baseRelayPins[16] = {50, 52, 42, 40, 38, 36, 22, 20, 19, 21, 35, 37, 39, 41, 51, 70};
    _currentProfileIndex = 0;
    _state = false;

    // incPin,  udPin,  csPin
    amplitudeKnob = new DigiPot(18, 23, 24);
    fineAdjustmentKnob = new DigiPot(5, 15, 16);
    coarseKnob = new DigiPot(6, 7, 1);

    profileArray = new Profile[numberOfProfiles];
    channelRelayPins = baseRelayPins;

    for (uint8_t i = 0; i < 16; i++)
    {
        pinMode(channelRelayPins[i], OUTPUT);   // set pin as output
        digitalWrite(channelRelayPins[i], LOW); // set initial state OFF for high trigger relay
    }

    _muscleTimer = muscleTimer;
    _muscleTimer->setSingleShot(true);

    Serial.println("IMS has been made"); //DEBUG
}

void among()
{
}

/**
 * @brief Start
 * 
 */
void IMS::Start(void)
{
    Serial.println("IMS Start"); //DEBUG
    _state = true;

    amplitudeKnob->set(profileArray[_currentProfileIndex].GetAmplitudeSetting());
    coarseKnob->set(profileArray[_currentProfileIndex].GetCoarseSetting());
    fineAdjustmentKnob->set(profileArray[_currentProfileIndex].GetFineSetting());

    SetRelayFromMuscleIndex(profileArray[_currentProfileIndex].GetMuscleIndex());
    //start timer
    _muscleTimer->setInterval(profileArray[_currentProfileIndex].GetTime());
    _muscleTimer->setOnTimer(&among);
    _muscleTimer->Start();
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

void IMS::SetRelayFromMuscleIndex(uint8_t muscleIndex)
{
    DisableRelay();
    switch (muscleIndex)
    {
    case VastusLateralis:
        digitalWrite(channelRelayPins[1], HIGH);
        break;
    case VastusMedialis:
        digitalWrite(channelRelayPins[2], HIGH);
        break;
    case Quadricep:
        digitalWrite(channelRelayPins[3], HIGH);
        break;
    case Gacilis:
        digitalWrite(channelRelayPins[4], HIGH);
        break;
    case Calves:
        digitalWrite(channelRelayPins[5], HIGH);
        break;
    }
}

void IMS::DisableRelay()
{
    for (int i = 0; i < 16; i++)
    {
        digitalWrite(channelRelayPins[i], LOW); // set initial state OFF for high trigger relay
    }
}
