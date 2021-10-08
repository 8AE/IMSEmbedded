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
    _maxNumberOfProfiles = 4; //TEMP MUST CHANGE FOR EEPROM
    Profile exampleProfiles[] = {
        {1, 1, 2, 6, 1, 4},
        {2, 1, 3, 7, 2, 5},
        {3, 1, 4, 8, 3, 6},
        {4, 1, 5, 9, 4, 7}};

    profileArray = exampleProfiles; //ALSO TEMP THIS IS FROM EEPROM ALSO
}

Profile TreatmentProfile::GetNextProfile()
{
    if (_currentProfileIndex > _maxNumberOfProfiles)
    {
        _currentProfileIndex = 0;
    }
    else
    {
        _currentProfileIndex++;
    }
    return profileArray[_currentProfileIndex];
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