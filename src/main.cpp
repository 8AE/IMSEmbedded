#include <Arduino.h>
#include "IMS.h"
#include "Button.h"

const uint8_t pinstartButton = 2;
const uint8_t pinprofileSelectButton = 3;
const uint8_t pinLed1 = 4;
const uint8_t pinLed2 = 5;

Button startButton(pinstartButton);
Button profileSelectButton(pinprofileSelectButton);
IMS ImsDevice;

void setup()
{
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);

  startButton.debounceMs = 500;
  profileSelectButton.debounceMs = 500;
}

void loop(void)
{
  uint16_t now = millis();
  ImsDevice.Start();
  startButton.poll(now);
  profileSelectButton.poll(now);

  startButton.wasPressed() ? digitalWrite(pinLed1, HIGH) : digitalWrite(pinLed1, LOW);
  profileSelectButton.wasPressed() ? digitalWrite(pinLed2, HIGH) : digitalWrite(pinLed2, LOW);
}
