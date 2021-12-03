/**
 * @file main.cpp
 * @author Ahmad El-baba (@8AE)
 * @brief 
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include <ezButton.h>
//#include <EEPROM.h>
#include "IMS.h"
#include "Led.h"
#include "timer.h"

const uint8_t pinstartButton = 27;
const uint8_t pinprofileSelectButton = 29;
uint8_t profileIndex;

ezButton startButton(pinstartButton);
ezButton profileSelectButton(pinprofileSelectButton);
Led profileLeds[] = {31, 33, 35, 37};
IMS ImsDevice(4);
TimerForMethods<IMS> *timer;

static bool firstRead = true;
static uint8_t index = 0;
uint8_t *mobileData;
static uint8_t fullSize = 0;

void setup()
{
  Serial.begin(9600); //DEBUG

  timer = new TimerForMethods<IMS>(&ImsDevice, &IMS::StartNextMuscle);
  ImsDevice.SetTimerPointer(timer);
  startButton.setDebounceTime(500);
  profileSelectButton.setDebounceTime(500);
  profileIndex = ImsDevice.GetCurrentProfileIndex();
  profileLeds[profileIndex].TurnOn();
  Serial.println(profileIndex);

  Serial.println("Class is alive");
}

void loop(void)
{
  timer->update();
  startButton.loop();
  profileSelectButton.loop();

  if (startButton.isPressed())
  {
    if (ImsDevice.GetState())
    {
      ImsDevice.Stop();
      Serial.println("Main Stop Button has been stopped");
    }
    else
    {
      ImsDevice.Start();
      Serial.println("Main Start Button has been started");
    }
  }

  if (profileSelectButton.isPressed())
  {
    profileLeds[profileIndex].TurnOff();

    profileIndex = ImsDevice.GetNextProfile();
    profileLeds[profileIndex].TurnOn();

    Serial.println(profileIndex);
    ImsDevice.PrintProfileInformation();
  }

  // Serial implementation starts here
  while (Serial.available() > 0 && firstRead)
  {
    fullSize = Serial.read();
    firstRead = false;
    mobileData = new uint8_t[fullSize];
  }

  while (Serial.available() > 0 && !firstRead)
  {
    mobileData[index] = Serial.read();
    //Serial.print(mobileData[index]);
    index++;
  }

  if (index >= fullSize && !firstRead)
  {
    // Serial.println(mobileData[0]);
    // Serial.println(mobileData[1]);
    index = 0;

    for (uint8_t i = 0; i < mobileData[0]; i++) //this should be the number of treatment profiles I hope
    {
      ImsDevice.treatmentProfileArray[i].profileArray = new Profile[mobileData[1]];
      for (uint8_t j = 0; j < mobileData[1]; j++) //number of muscle profiles
      {
        ImsDevice.treatmentProfileArray[i].profileArray[j].SetMuscleIndex(mobileData[2 + j]);
        ImsDevice.treatmentProfileArray[i].profileArray[j].SetCoarseSetting(mobileData[3 + j]);
        ImsDevice.treatmentProfileArray[i].profileArray[j].SetFineSetting(mobileData[4 + j]);
        ImsDevice.treatmentProfileArray[i].profileArray[j].SetAmplitudeSetting(mobileData[5 + j]);
        ImsDevice.treatmentProfileArray[i].profileArray[j].SetTime(mobileData[6 + j]);

        Serial.println("Muscle:");
        Serial.println(ImsDevice.treatmentProfileArray[i].profileArray[j].GetMuscleIndex());
        Serial.println("Coarse:");
        Serial.println(ImsDevice.treatmentProfileArray[i].profileArray[j].GetCoarseSetting());
        Serial.println("Fine:");
        Serial.println(ImsDevice.treatmentProfileArray[i].profileArray[j].GetFineSetting());
        Serial.println("Amplitude:");
        Serial.println(ImsDevice.treatmentProfileArray[i].profileArray[j].GetAmplitudeSetting());
        Serial.println("Time:");
        Serial.println(ImsDevice.treatmentProfileArray[i].profileArray[j].GetTime());
      }
    }
    firstRead = true;
  }
}
