#ifndef DUALPOLE_H
#define DUALPOLE_H

#include <Arduino.h>
#include "Switch.h"

class DualPole : public Switch {
  private:
    byte pin2;
    byte bitPos2;
    bool isMuxPinned2 = false;
    
    int lastButtonState2 = LOW;   // previous reading from the input pin

  public:
    DualPole(Mux &mux, byte pin, byte pin2, byte bitPos, byte bitPos2, byte CC, bool isMuxPinned, bool isMuxPinned2);
    DualPole(byte pin, byte pin2, byte bitPos, byte bitPos2, byte CC);
    
    void init() override;
    void update() override;
    void pinUpdate(byte pinU, byte pinPosU, bool isMux, int &lastState);
    byte getPin(byte id);
};

#endif
