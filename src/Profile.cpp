/**
 * @file Profile.cpp
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

Profile::Profile()
{
}

void Profile::SetMuscleIndex(uint8_t _muscleIndex)
{
    muscleIndex = _muscleIndex;
}
void Profile::SetCoarseSetting(uint8_t _coarseSetting)
{
    coarseSetting = _coarseSetting;
}
void Profile::SetFineSetting(uint8_t _fineSetting)
{
    fineSetting = _fineSetting;
}
void Profile::SetAmplitudeSetting(uint8_t _amplitudeSetting)
{
    amplitudeSetting = _amplitudeSetting;
}
void Profile::SetTime(uint16_t _time)
{
    time = _time;
}