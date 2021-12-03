/**
 * @file Profile.h
 * @author Ahmad El-baba (@8AE)
 * @brief 
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#pragma once

using namespace std;

class Profile
{
private:
    uint8_t muscleIndex;
    uint8_t coarseSetting;    //0 - 30v
    uint8_t fineSetting;      //1 - 100
    uint8_t amplitudeSetting; //1 - 100
    uint8_t time;             // min 1 - 20

public:
    Profile();
    Profile(uint8_t _muscleIndex, uint8_t _coarseSetting, uint8_t _fineSetting, uint8_t _amplitudeSetting, uint8_t _time);
    uint8_t GetTime() { return time; }
    uint8_t GetFineSetting() { return fineSetting; }
    uint8_t GetAmplitudeSetting() { return amplitudeSetting; }
    uint8_t GetCoarseSetting() { return coarseSetting; }
    uint8_t GetMuscleIndex() { return muscleIndex; }

    void SetMuscleIndex(uint8_t _muscleIndex);
    void SetCoarseSetting(uint8_t _coarseSetting);
    void SetFineSetting(uint8_t _fineSetting);
    void SetAmplitudeSetting(uint8_t _amplitudeSetting);
    void SetTime(uint8_t _time);
};
