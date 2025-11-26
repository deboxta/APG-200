#ifndef DUALPOLE_H
#define DUALPOLE_H

#include "Switch.h"

class DualPole : public Switch {
  private:
    byte pin2;
    byte bitPos2;
    bool isMuxPinned2 = false;
        
    byte buttonState2;             // current reading from the input pin

    byte lastButtonState2 = LOW;   // previous reading from the input pin
    unsigned long lastDebounceTime2 = 0;  // the last time the output pin was toggled

  public:
    DualPole(Mux* mux, byte pin, byte pin2, byte bitPos, byte bitPos2, byte CC, bool isMuxPinned, bool isMuxPinned2);
    DualPole(byte pin, byte pin2, byte bitPos, byte bitPos2, byte CC);

    void init();
    void Setup(byte &pinU, byte &bitPosU, bool &mux, byte &state);
    void update() override;
    void pinUpdate(byte &pinU, byte &pinPosU, bool &isMux, byte &lastState, unsigned long &lastDebounceT, byte &state);
    byte getPin(byte id);
};

#endif
