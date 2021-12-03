/**
 * @file TreatmentProfile.cpp
 * @author Ahmad El-baba (@8AE)
 * @brief 
 * @version 0.1
 * @date 2021-10-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "TreatmentProfile.h"

TreatmentProfile::TreatmentProfile()
{
    _maxNumberOfProfiles = 4;
    _currentProfileIndex = 0;
    profileArray = new Profile[5]{
        {1, 50, 50, 20, 5},
        {2, 50, 50, 40, 5},
        {3, 50, 50, 60, 5},
        {3, 50, 50, 60, 5},
        {4, 50, 50, 100, 5}};
}

uint8_t TreatmentProfile::GetNextProfile()
{
    if (_currentProfileIndex >= _maxNumberOfProfiles - 1)
    {
        _currentProfileIndex = 0;
    }
    else
    {
        _currentProfileIndex++;
    }
    return _currentProfileIndex;
}

Profile TreatmentProfile::GetCurrentProfile()
{
    return profileArray[_currentProfileIndex];
}

Profile TreatmentProfile::GetProfile(uint8_t index)
{
    return profileArray[index];
}

void TreatmentProfile::SetCurrentProfileIndex(uint8_t index)
{
    _currentProfileIndex = index;
}