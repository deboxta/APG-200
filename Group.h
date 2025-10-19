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
    int index = 0;
    Switch switches[];
  public:
    Group(byte groupCC);
    void init();
    void update();
    byte getGroupCC();
    byte getBitMask();
    byte getValue();
    void addSwitch(Switch sw);
};

#endif
