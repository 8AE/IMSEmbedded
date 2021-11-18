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

  if (Serial.available())
  {
    char fullsize = Serial.read();
    char *mobileData = new char[fullsize];
    if (Serial.available() >= fullsize)
    {
      for (size_t i = 0; i < fullsize; i++)
      {
        mobileData[i] = Serial.read(); //get all the data
      }
    }
    for (size_t i = 0; i < mobileData[0]; i++) //this should be the number of treatment profiles I hope
    {
      /*code */
    }
  }
}
