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
#include "TimerObject.h"

const uint8_t pinstartButton = 73;
const uint8_t pinprofileSelectButton = 71;
uint8_t profileIndex;

ezButton startButton(pinstartButton);
ezButton profileSelectButton(pinprofileSelectButton);
Led profileLeds[] = {59, 57, 55, 53};
TimerObject *muscleTimer = new TimerObject(10000); //will call the callback in the interval of 1000 ms
IMS ImsDevice(4, muscleTimer);

void setup()
{
  startButton.setDebounceTime(1000);
  profileSelectButton.setDebounceTime(1000);
  profileIndex = ImsDevice.GetCurrentProfileIndex();
  profileLeds[profileIndex].TurnOn();

  Serial.begin(9600); //DEBUG
}

void loop(void)
{
  muscleTimer->Update();
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
  }
}
