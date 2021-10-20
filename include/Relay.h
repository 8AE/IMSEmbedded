/**
 * @file Relay.h
 * @author Ahmad El-baba (@8AE)
 * @brief 
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#pragma once

using namespace std;

class Relay
{
private:
    const uint8_t *channelArray;

public:
    Relay(const uint8_t *_channelArray);
    void SetChannelTo(uint8_t channel, uint8_t state);
    void SetAllChannelsTo(uint8_t state);
    void ConfigureAllChannelsTo(uint8_t mode);
};
