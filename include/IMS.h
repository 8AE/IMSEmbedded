/*
    Main IMS class for Senior Design 2
    Spring 2021 by Ahmad El-Baba
*/

#include <Arduino.h>
#include "Profile.h"
#pragma once

using namespace std;

class IMS
{
protected:
    boolean _state; //state of IMS machine
    uint8_t _currentProfileIndex;
    uint8_t _maxNumberOfProfiles;
    Profile profileArray[];

public:
    IMS(void);
    void Start();
    void Stop();
    void SelectProfile();
    uint8_t GetCurrentProfileIndex() { return _currentProfileIndex; }
    boolean GetState() { return _state; }
};
