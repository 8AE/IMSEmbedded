/*
    An object oriented approach to a latched button
    Jan 2015, for the Arduino forum, by MattS-UK

    Compiled and tested on a Mega 2560 R3

    Modified by Ahmad El-Baba
*/

#include "Button.h"

//constructor
Button::Button(uint8_t pin) {
  _pin = pin;
  _state = false;
  _startDebounce = false;
  _wasPressed = false;
  
  debounceMs = 500;
  pinMode(_pin, INPUT_PULLUP);
}

//refresh the button state
void Button::poll(uint16_t now){
  
  //pullup resistors cause the 
  // button to be HIGH when open 
  // so we invert the hardware state
  _state = !digitalRead(_pin);
  
  //when the button state is false, reset the debounce time
  if(!_state){
    _startDebounce = 0;
  }
  else {
    //start debounce time
    if(!_startDebounce) {
      _startDebounce = now;
    }
    else {
      //latch the button if it is still pressed when the debounce time expires
      if(now - _startDebounce > debounceMs) {
        _wasPressed = true;
      }    
    }
  } 
}

//reset the button
void Button::reset(void) {
  _wasPressed = false;
  _startDebounce = 0;
}
