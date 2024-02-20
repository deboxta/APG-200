#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <Arduino.h>

class Button {
  private:
    byte pin;
    byte CC;
    byte state;
    byte lastState;
    byte value;

    //Debounce buttons
    unsigned long lastDebounceTime = 0;
    unsigned long debounceTimer = 0;
    unsigned long debounceDelay = 70;

  public:
    Button(byte pin, byte CC, byte value);

    void init();
    void update();

    byte getState();
    bool isPressed();
    byte getValue();
    byte getCC();

};

#endif

