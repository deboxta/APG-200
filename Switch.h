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
    byte groupCC;
    byte value = 0b00000000;

    Mux &mux;
    bool isMuxPinned = true;

    byte getPin();

  public:
    Switch(Mux &mux, byte pin1, byte pin2, byte bitPos1, byte bitPos2, byte groupCC, bool isMuxPinned);
    Switch(Mux &mux, byte pin1, byte bitPos1, byte groupCC, bool isMuxPinned);
    Switch(Mux &mux, byte pin1, byte pin2, byte bitPos1, byte bitPos2, byte groupCC);
    Switch(Mux &mux, byte pin1, byte bitPos1, byte groupCC);
    void init();
    void update();
    byte getGroupCC();
};

#endif
