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
    bool pressed;

    //Debounce buttons
    unsigned long lastDebounceTime = 0;
    const unsigned long debounceDelay = 50;

  public:
    Button(byte pin, byte CC, byte value);

    void init();
    void update();

    bool isPressed();
    byte getValue();
    byte getCC();

};

#endif
