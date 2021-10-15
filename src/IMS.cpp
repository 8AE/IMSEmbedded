/**
 * @file Ims.cpp
 * @author Ahmad El-baba (@8AE)
 * @brief 
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include "IMS.h"
#include "TreatmentProfile.h"
#include "timer.h"
#include "Relay.h"

/**
 * @brief Construct a new IMS::IMS object
 * 
 * @param numberOfProfiles 
 */
IMS::IMS(uint8_t numberOfProfiles)
{
    _maxNumberOfTreatmentProfiles = numberOfProfiles;
    _currentTreatmentProfileIndex = 0;
    _state = false;

    // incPin,  udPin,  csPin
    amplitudeKnob = new DigiPot(9, 10, 11);
    fineAdjustmentKnob = new DigiPot(5, 6, 7);
    coarseKnob = new DigiPot(2, 3, 4);

    TreatmentProfile exampleProfiles[4] = {};
    treatmentProfileArray = exampleProfiles;

    const uint8_t baseRelayPins[16] = {38, 40, 42, 44, 46, 48, 50, 52, 53, 51, 49, 47, 45, 43, 41, 39};
    const uint8_t *tempPointer = baseRelayPins;
    mainRelay = new Relay(tempPointer);
}

void IMS::StartNextMuscle()
{
    Serial.println("Timer Callback");
    if (treatmentProfileArray[_currentTreatmentProfileIndex].GetNextProfile() == 0) //this means we looped back and ended
    {
        Stop();
    }
    else
    {
        Start();
    }
}

void IMS::SetTimerPointer(TimerForMethods<IMS> *timerPointer)
{
    timer = timerPointer;
}

/**
 * @brief Start
 * 
 */
void IMS::Start(void)
{
    Serial.println("IMS Start"); //DEBUG
    _state = true;

    amplitudeKnob->set(treatmentProfileArray[_currentTreatmentProfileIndex].GetCurrentProfile().GetAmplitudeSetting());
    coarseKnob->set(treatmentProfileArray[_currentTreatmentProfileIndex].GetCurrentProfile().GetCoarseSetting());
    fineAdjustmentKnob->set(treatmentProfileArray[_currentTreatmentProfileIndex].GetCurrentProfile().GetFineSetting());

    SetRelayFromMuscleIndex(treatmentProfileArray[_currentTreatmentProfileIndex].GetCurrentProfile().GetMuscleIndex());
    timer->setTimeout(treatmentProfileArray[_currentTreatmentProfileIndex].GetCurrentProfile().GetTime() * 1000);
    timer->start();
}

/**
 * @brief 
 * 
 */
void IMS::Stop(void)
{
    Serial.println("IMS Stop"); //DEBUG
    _state = false;

    amplitudeKnob->reset();
    coarseKnob->reset();
    fineAdjustmentKnob->reset();
    mainRelay->SetAllChannelsTo(false);
    timer->stop();
}

/**
 * @brief 
 * 
 * @param index 
 */
void IMS::SelectProfile(uint8_t index)
{
    _currentTreatmentProfileIndex = index;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t IMS::GetNextProfile()
{
    if (_currentTreatmentProfileIndex > _maxNumberOfTreatmentProfiles - 1)
    {
        _currentTreatmentProfileIndex = 0;
    }
    else
    {
        _currentTreatmentProfileIndex++;
    }
    return _currentTreatmentProfileIndex;
}

void IMS::SetRelayFromMuscleIndex(uint8_t muscleIndex)
{
    mainRelay->SetAllChannelsTo(false);
    switch (muscleIndex)
    {
    case VastusLateralis:
        mainRelay->SetChannelTo(1, true);
        break;
    case VastusMedialis:
        mainRelay->SetChannelTo(2, true);
        break;
    case Quadricep:
        mainRelay->SetChannelTo(3, true);
        break;
    case Gacilis:
        mainRelay->SetChannelTo(4, true);
        break;
    case Calves:
        mainRelay->SetChannelTo(5, true);
        break;
    default:
        mainRelay->SetAllChannelsTo(true);
        break;
    }
}
