#ifndef MUX
#define MUX

#include "Arduino.h"
#include <inttypes.h>

class Mux
{
  public:
    Mux(byte primaryPin, uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3);
    void channel(uint8_t channel);
    byte getPrimaryPin();
    void init();
  private:
    uint8_t _s0;
    uint8_t _s1;
    uint8_t _s2;
    uint8_t _s3;
    uint8_t _channel;

    byte primaryPin;
};

#endif
