/**
 * @file IMS.h
 * @author Ahmad El-baba (@8AE)
 * @brief 
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include <DigiPotX9Cxxx.h>
#include "Profile.h"
#pragma once

using namespace std;

class IMS
{
protected:
    boolean _state; //state of IMS machine
    uint8_t _currentProfileIndex;
    // incPin,  udPin,  csPin
    DigiPot *amplitudeKnob;
    DigiPot *fineAdjustmentKnob;
    DigiPot *coarseKnob;

    Profile profileArray[4] = {};

public:
    IMS(uint8_t numberOfProfiles);
    void Start();
    void Stop();
    void SelectProfile(uint8_t index);
    uint8_t GetNextProfile();
    uint8_t GetCurrentProfileIndex() { return _currentProfileIndex; }
    boolean GetState() { return _state; }
};
