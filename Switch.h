#ifndef MY_SWITCH_H
#define MY_SWITCH_H

#include <Arduino.h>
#include "Mux.h"

class Switch {
  private:

  public:
    Mux* mux;
    byte pin;
    byte bitPos;
    byte CC;
    byte value = 0b00000000;

    bool isMuxPinned = false;
    
    // Variables will change:
    byte buttonState;             // current reading from the input pin
    byte lastButtonState = LOW;   // previous reading from the input pin
    
    // the following variables are unsigned longs because the time, measured in milliseconds,
    // will quickly become a bigger number than can be stored in an int.
    unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
    const unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
  
    Switch(Mux* mux, byte pin, byte bitPos, byte CC, bool isMuxPinned);
    Switch(byte pin, byte bitPos, byte CC);

    virtual void init() = 0;
    virtual void update() = 0;
    byte getValue();
    virtual byte getPin();
    byte getCC();
    virtual ~Switch() {} 
};

#endif
