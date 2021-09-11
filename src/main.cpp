#include <Arduino.h>
#include "IMS.h"

IMS *mainProgram;

void setup() {
  mainProgram = new IMS();
  pinMode(PB5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  mainProgram->Start();
}