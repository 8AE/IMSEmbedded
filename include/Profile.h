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
protected:
    uint8_t numberOfChannels; //Hey ahmad this may end up being a bit map or something
    uint8_t channel[8];
    uint8_t intensity;      //0 - 30v
    uint16_t frequencyInHz; //1 - 100
    uint16_t time;          // min 1 - 20

public:
    Profile(void);
    uint16_t GetTime() { return time; }
    uint16_t GetFrequencyInHz() { return frequencyInHz; }
};
