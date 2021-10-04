/*
    Main IMS class for Senior Design 2
    Spring 2021 by Ahmad El-Baba
*/

#include <Arduino.h>
#include "IMS.h"

IMS::IMS(uint8_t numberOfProfiles)
{
    _currentProfileIndex = 0;
    _state = false;
    Serial.println("IMS has been made"); //DEBUG
}

/**
* start everything
* this is where we adjust all the potentiometers
* set thevalues
* and start
*/
void IMS::Start(void)
{
    Serial.println("IMS Start"); //DEBUG
    _state = true;
    /*
    * configure all pins
    * start timer
    * start channel
    */
}

/**
* Stop the IMS Device
*/
void IMS::Stop(void)
{
    Serial.println("IMS Stop"); //DEBUG
    _state = false;
    /*
    * configure all pins
    * start timer
    * start channel
    */
}

/**
* Select profile from specific index
*/
void IMS::SelectProfile(uint8_t index)
{
    _currentProfileIndex = index;
}

/**
* Gets ands sets the next profile index
* Loops after 3
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
