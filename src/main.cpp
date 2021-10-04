#include <Arduino.h>
#include <ezButton.h>
#include <EEPROM.h>
#include "IMS.h"
#include "Button.h"

const uint8_t pinstartButton = 8;
const uint8_t pinprofileSelectButton = 7;
const uint8_t pinLed1 = 4;
const uint8_t pinLed2 = 5;
uint8_t profileIndex;

ezButton startButton(pinstartButton);
ezButton profileSelectButton(pinprofileSelectButton);
IMS ImsDevice(4);

void setup()
{
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);

  startButton.setDebounceTime(1000);
  profileSelectButton.setDebounceTime(1000);
  profileIndex = ImsDevice.GetCurrentProfileIndex();

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
    profileIndex = ImsDevice.GetNextProfile();

    Serial.println(profileIndex);
  }
}
