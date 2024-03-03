#ifndef GROUP_H
#define GROUP_H

#include <Arduino.h>
#include "Switch.h"

class Group {
  private:
    byte groupCC;
    byte bitMask;
    int value;
    int lastValue;
    Switch switches[];
  public:
    Group(byte groupCC, Switch switches[]);
    void init();
    void update();
    byte getGroupCC();
    byte getBitMask();
    byte getValue();
};

#endif
