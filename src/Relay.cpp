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

    ConfigureAllChannelsTo(OUTPUT);
    SetAllChannelsTo(HIGH);
}

void Relay::SetAllChannelsTo(uint8_t state)
{
    for (uint8_t i = 0; i < 16; i++)
    {
        digitalWrite(channelArray[i], state);
    }
}

void Relay::ConfigureAllChannelsTo(uint8_t mode)
{
    for (uint8_t i = 0; i < 16; i++)
    {
        pinMode(channelArray[i], OUTPUT); // set pin as output
    }
}

void Relay::SetChannelTo(uint8_t channel, uint8_t state)
{
    Serial.println(channelArray[channel]);
    digitalWrite(channelArray[channel], state);
}