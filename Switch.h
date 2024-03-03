#ifndef MY_SWITCH_H
#define MY_SWITCH_H

#include <Arduino.h>

class Switch {
  private:
    byte pins;
    byte groupCC;
    byte bitPos[];
    int value = 0; //mapped values of pot (sent)
  public:
    Switch(byte pin, byte groupCC, byte bitPos[]);
    void init();
    void update();
    byte getGroupCC();
};

#endif
