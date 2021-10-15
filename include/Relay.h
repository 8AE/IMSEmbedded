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
    bool isInvertedLogic;

public:
    Relay(const uint8_t *_channelArray);
    void SetLogicTrigger(bool logic);
    void SetChannelTo(uint8_t channel, bool state);
    void SetAllChannelsTo(bool state);
    void ConfigureAllChannelsTo(uint8_t mode);
};
