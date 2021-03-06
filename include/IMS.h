/**
 * @file IMS.h
 * @author Ahmad El-baba (@8AE)
 * @brief 
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include <DigiPotX9Cxxx.h>
#include "Profile.h"
#include "TreatmentProfile.h"
#include "timer.h"
#include "Relay.h"

#pragma once

using namespace std;

enum
{
    VastusLateralis = 1,
    VastusMedialis,
    Quadricep,
    Gacilis,
    Hamstring,
    Calves
};

class IMS
{
private:
    boolean _state; //state of IMS machine
    uint8_t _currentTreatmentProfileIndex;
    uint8_t _maxNumberOfTreatmentProfiles;

    DigiPot *amplitudeKnob;
    DigiPot *fineAdjustmentKnob;
    DigiPot *coarseKnob;

    void SetRelayFromMuscleIndex(uint8_t muscleIndex);
    TimerForMethods<IMS> *timer;

    const uint8_t *RelayArray = NULL;
    void ResetRelays();

public:
    TreatmentProfile *treatmentProfileArray;
    IMS(uint8_t numberOfProfiles);
    void StartNextMuscle();
    void SetTimerPointer(TimerForMethods<IMS> *timerPointer);
    void Start();
    void Stop();
    void SelectProfile(uint8_t index);
    void PrintProfileInformation();
    uint8_t GetNextProfile();
    uint8_t GetCurrentProfileIndex() { return _currentTreatmentProfileIndex; }
    boolean GetState() { return _state; }
};
