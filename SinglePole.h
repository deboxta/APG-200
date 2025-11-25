#ifndef SINGLEPOLE_H
#define SINGLEPOLE_H

#include "Switch.h"

class SinglePole : public Switch {
  private:

  public:
    SinglePole(Mux* mux, byte pin, byte bitPos, byte CC, bool isMuxPinned);
    SinglePole(byte pin, byte bitPos, byte CC);
    
    void update() override;
    byte getPin() override;
};

#endif
