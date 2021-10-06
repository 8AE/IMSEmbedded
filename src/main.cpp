#include <Arduino.h>
#include <ezButton.h>
#include <EEPROM.h>
#include "IMS.h"
#include "Button.h"
#include "Led.h"

const uint8_t pinstartButton = 73;
const uint8_t pinprofileSelectButton = 71;
uint8_t profileIndex;

ezButton startButton(pinstartButton);
ezButton profileSelectButton(pinprofileSelectButton);
IMS ImsDevice(4);
Led profileLeds[] = {59, 57, 55, 53};

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
  startButton.loop();
  profileSelectButton.loop();

  if (startButton.isPressed())
  {
    ImsDevice.Start();
    Serial.println("Main Start Button has been started");
  }

  if (profileSelectButton.isPressed())
  {
    profileLeds[profileIndex].TurnOff();

    profileIndex = ImsDevice.GetNextProfile();
    profileLeds[profileIndex].TurnOn();

    Serial.println(profileIndex);
  }
}
