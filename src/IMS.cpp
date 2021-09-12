/*
    Main IMS class for Senior Design 2
    Spring 2021 by Ahmad El-Baba
*/

#include <Arduino.h>
#include "IMS.h"

IMS::IMS(void)
{
    Serial.println("IMS has been made"); //DEBUG
}

void IMS::Start(void)
{
    Serial.println("IMS Start"); //DEBUG
}

void IMS::Stop(void)
{
    Serial.println("IMS Stop"); //DEBUG
}

void IMS::SelectProfile(void)
{
}
