/**
 * @file Relay.cpp
 * @author Ahmad El-baba (@8AE)
 * @brief 
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Relay.h"

Relay::Relay(const uint8_t *_channelList)
{
    channelArray = _channelList;
    isInvertedLogic = true;
    ConfigureAllChannelsTo(OUTPUT);
    SetAllChannelsTo(false);
}

void Relay::SetAllChannelsTo(bool state)
{
    for (uint8_t i = 0; i < sizeof(channelArray) / sizeof(uint8_t); i++)
    {
        if (isInvertedLogic)
        {
            digitalWrite(channelArray[i], !state);
        }
        else
        {
            digitalWrite(channelArray[i], state);
        }
    }
}

void Relay::ConfigureAllChannelsTo(uint8_t mode)
{
    for (uint8_t i = 0; i < sizeof(channelArray) / sizeof(uint8_t); i++)
    {
        pinMode(channelArray[i], OUTPUT); // set pin as output
    }
}

void Relay::SetLogicTrigger(bool trigger)
{
    isInvertedLogic = trigger;
}

void Relay::SetChannelTo(uint8_t channel, bool state)
{
    if (isInvertedLogic)
    {
        digitalWrite(channelArray[channel], !state);
    }
    else
    {
        digitalWrite(channelArray[channel], state);
    }
}