/**
 * @file TreatmentProfile.h
 * @author Ahmad El-baba (@8AE)
 * @brief 
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include "Profile.h"
#pragma once

using namespace std;

class TreatmentProfile
{
private:
    uint8_t _currentProfileIndex;
    uint8_t _maxNumberOfProfiles;
    Profile *profileArray;

public:
    TreatmentProfile(void);
    uint8_t GetNextProfile();
    Profile GetCurrentProfile();
    Profile GetProfile(uint8_t index);
    uint8_t GetCurrentProfileIndex() { return _currentProfileIndex; }
    void SetCurrentProfileIndex(uint8_t index);
};
