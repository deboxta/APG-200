#ifndef MY_SWITCH_H
#define MY_SWITCH_H

#include <Arduino.h>
#include "Mux.h"

class Switch {
  private:
    byte pin1;
    byte pin2 = -1;
    byte bitPos1;
    byte bitPos2 = -1;
    byte CC;
    byte value = 0b00000000;

    Mux &mux;
    bool isMuxPinned = true;

    byte getPin();

    // Variables will change:
    int buttonState;             // current reading from the input pin
    int lastButtonState = LOW;   // previous reading from the input pin
    
    // the following variables are unsigned longs because the time, measured in milliseconds,
    // will quickly become a bigger number than can be stored in an int.
    unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
    unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

  public:
    Switch(Mux &mux, byte pin1, byte pin2, byte bitPos1, byte bitPos2, byte CC, bool isMuxPinned);
    Switch(Mux &mux, byte pin1, byte bitPos1, byte CC, bool isMuxPinned);
    Switch(Mux &mux, byte pin1, byte pin2, byte bitPos1, byte bitPos2, byte CC);
    Switch(Mux &mux, byte pin1, byte bitPos1, byte CC);
    void init();
    void update();
    byte getCC();
    byte getValue();
};

#endif
