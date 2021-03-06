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
    fineAdjustmentKnob = new DigiPot(6, 7, 8);
    coarseKnob = new DigiPot(3, 4, 5);
    treatmentProfileArray = new TreatmentProfile[4];

    RelayArray = new uint8_t[16]{38, 40, 42, 44, 46, 48, 50, 52, 53, 51, 49, 47, 45, 43, 41, 39};
    for (uint8_t i = 0; i < 16; i++)
    {
        pinMode(RelayArray[i], OUTPUT); // set pin as output
        digitalWrite(RelayArray[i], HIGH);
    }
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

    Serial.print("\n Amplitude:");
    Serial.print(amplitudeKnob->get());
    Serial.print("\n Coarase:");
    Serial.print(coarseKnob->get());
    Serial.print("\n Fine:");
    Serial.print(fineAdjustmentKnob->get());

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
    Serial.println("IMS Stop");
    _state = false;

    amplitudeKnob->reset();
    coarseKnob->reset();
    fineAdjustmentKnob->reset();
    _currentTreatmentProfileIndex = 0;
    ResetRelays();
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
    if (_currentTreatmentProfileIndex >= _maxNumberOfTreatmentProfiles - 1)
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
    ResetRelays();
    switch (muscleIndex)
    {
    case VastusLateralis:
        digitalWrite(RelayArray[0], LOW);
        digitalWrite(RelayArray[15], LOW);
        break;
    case VastusMedialis:
        digitalWrite(RelayArray[1], LOW);
        digitalWrite(RelayArray[14], LOW);
        break;
    case Quadricep:
        digitalWrite(RelayArray[2], LOW);
        digitalWrite(RelayArray[13], LOW);
        break;
    case Gacilis:
        digitalWrite(RelayArray[3], LOW);
        digitalWrite(RelayArray[12], LOW);
        break;
    case Hamstring:
        digitalWrite(RelayArray[4], LOW);
        digitalWrite(RelayArray[11], LOW);
        digitalWrite(RelayArray[5], LOW);
        digitalWrite(RelayArray[10], LOW);
        break;
    case Calves:
        digitalWrite(RelayArray[6], LOW);
        digitalWrite(RelayArray[9], LOW);
        digitalWrite(RelayArray[7], LOW);
        digitalWrite(RelayArray[8], LOW);
        break;
    default:
        break;
    }
}

void IMS::PrintProfileInformation()
{
    Serial.print("\n Current Treatment profile Index:");
    Serial.print(_currentTreatmentProfileIndex);
    Serial.print("\n Current Muscle profile Index:");
    Serial.print(treatmentProfileArray[_currentTreatmentProfileIndex].GetCurrentProfileIndex());
    Serial.print("\n Muscle Index:");
    Serial.print(treatmentProfileArray[_currentTreatmentProfileIndex].GetCurrentProfile().GetMuscleIndex());
    Serial.print("\n Coarse Setting:");
    Serial.print(treatmentProfileArray[_currentTreatmentProfileIndex].GetCurrentProfile().GetCoarseSetting());
    Serial.print("\n Fine Setting:");
    Serial.print(treatmentProfileArray[_currentTreatmentProfileIndex].GetCurrentProfile().GetFineSetting());
    Serial.print("\n Amplitude Setting:");
    Serial.print(treatmentProfileArray[_currentTreatmentProfileIndex].GetCurrentProfile().GetAmplitudeSetting());
    Serial.print("\n Time:");
    Serial.print(treatmentProfileArray[_currentTreatmentProfileIndex].GetCurrentProfile().GetTime());
}

void IMS::ResetRelays()
{
    for (uint8_t i = 0; i < 16; i++)
    {
        digitalWrite(RelayArray[i], HIGH);
    }
}
