/*
    Profile containing singal information
    Used for Senior Design 2
    Spring 2021 by Ahmad El-Baba
*/

#include <Arduino.h>
#pragma once

using namespace std;

class Profile
{
protected:
    boolean _state; //state of IMS machine
    uint8_t _currentProfileIndex;
    uint8_t _maxNumberOfProfiles = 4;

public:
    Profile(void);
};
