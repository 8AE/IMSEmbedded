#include <Arduino.h>
#include "IMS.h"
#include "Button.h"

const uint8_t pinstartButton = 8;
const uint8_t pinprofileSelectButton = 7;
const uint8_t pinLed1 = 4;
const uint8_t pinLed2 = 5;

Button startButton(pinstartButton);
Button profileSelectButton(pinprofileSelectButton);
IMS ImsDevice;

void setup()
{
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);

  startButton.debounceMs = 1000;
  profileSelectButton.debounceMs = 500;

  Serial.begin(9600); //DEBUG
}

void loop(void)
{
  uint16_t now = millis();

  startButton.poll(now);
  profileSelectButton.poll(now);

  if (!startButton.getState())
  {
    ImsDevice.Start();
    Serial.println("Main Start Button has been started");
  }

  profileSelectButton.wasPressed() ? digitalWrite(pinLed2, HIGH) : digitalWrite(pinLed2, LOW);
}
